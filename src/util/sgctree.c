/*
  Copyright (C) <2009> <Alexandre Xavier Falcão and João Paulo Papa>

  This program is free software; you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation; either version 2 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program; if not, write to the Free Software
  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA

  please see full copyright in COPYING file.
  -------------------------------------------------------------------------
  written by A.X. Falcão <afalcao@ic.unicamp.br> and by J.P. Papa
  <papa.joaopaulo@gmail.com>, Oct 20th 2008

  This program is a collection of functions to manage the Optimum-Path Forest (OPF)
  classifier.*/

#include "sgctree.h"

SgCTree *CreateSgMaxTree(Subgraph *g){
    SgCTree *ctree=(SgCTree *)calloc(1,sizeof(SgCTree));
    int *dad,*cmap, *tmp, *level, Imax, *val;
    int i,r,p,q,rp,rq,n;
    GQueue *Q;
    int *nsons=NULL;
    int *size=NULL;
    Set *adj;

    n           = g->nnodes;
    level       = AllocIntArray(n);
    val         = AllocIntArray(n);
    Imax        = INT_MIN;

    for (p=0; p < n; p++)
    {
        val[p] = (int)g->node[p].dens;
        if (val[p]>Imax)
            Imax=val[p];
    }

    ctree->cmap = AllocIntArray(n);
    cmap        = ctree->cmap;
    ctree->root = NIL; /* Tree is empty */
    dad         = AllocIntArray(n);
    size        = AllocIntArray(n);
    Q           = CreateGQueue(Imax+1,n,level);
    SetTieBreak(Q,LIFOBREAK);

    for (p=0; p < n; p++)
    {
        dad[p]  =NIL;
        cmap[p] =p;
        level[p]=Imax-val[p];
        size[p]=1;
        InsertGQueue(&Q,p);
    }

    while (!EmptyGQueue(Q))
    {
        p  = RemoveGQueue(Q);
        rp = SgRepresentative(cmap,p);

        adj = g->node[p].adj;
        while (adj != NULL)
        {
            q = adj->elem;
            if (val[p]==val[q])  /* propagate component */
            {
                if (Q->L.elem[q].color==GRAY)
                {
                    cmap[q]=rp;
                    if (p==rp) size[rp]=size[rp]+1;
                    UpdateGQueue(&Q,q,level[p]);
                }
            }
            else
            {
                if (val[p] < val[q]) /* find current dad of rq */
                {
                    rq = SgRepresentative(cmap,q);
                    r  = SgAncestor(dad,cmap,rq);
                    if (r == NIL)   /* rp is dad of the rq */
                    {
                        dad[rq]=rp;
                    }
                    else
                    {
                        if (val[r]==val[rp])  /* merge components */
                        {
                            if (r != rp)
                            {
                                if (size[rp] <= size[r])
                                {
                                    cmap[rp] = r;
                                    size[r]  = size[r] + size[rp];
                                    rp = r;
                                }
                                else
                                {
                                    cmap[r]  = rp;
                                    size[rp] = size[rp] + size[r];
                                }
                            }
                        }
                        else   /* val[r] > val[rp] */
                        {
                            dad[r] = rp; /* rp is dad of r */
                        }
                    }
                }
            }
            adj = adj->next;
        }
    }

    free(size);
    DestroyGQueue(&Q);
    free(level);

    /* Compress cmap map and count number of nodes */

    ctree->numnodes = 0;
    for (p=0; p < n; p++)
    {
        if (dad[cmap[p]]!=NIL)
            r = cmap[p];
        cmap[p] = SgRepresentative(cmap,p);

        if (cmap[p]==p)
            ctree->numnodes++;
    }

    /* Create and initialize nodes of the MaxTree. */

    ctree->node = (SgCTNode *)calloc(ctree->numnodes,sizeof(SgCTNode));
    tmp         = AllocIntArray(n);
    for (p=0; p < n; p++)
    {
        tmp[p]=NIL;
    }

    i = 0;
    for (p=0; p < n; p++)
    {
        if (cmap[p]==p)
        {
            ctree->node[i].level = val[p];
            ctree->node[i].comp  = p;
            tmp[p]               = i;
            ctree->node[i].dad   = NIL;
            ctree->node[i].son   = NULL;
            ctree->node[i].numsons = 0;
            ctree->node[i].size  = 0;
            i++;
        }
    }

    free(val);

    /* Make the component map to point back to the maxtree. */

    for (p=0; p < n; p++)
    {
        if (tmp[p] == NIL)
            tmp[p] = tmp[cmap[p]];
    }

    for (p=0; p < n; p++)
    {
        cmap[p] = tmp[p];
    }
    free(tmp);

    /* Copy dad information to the maxtree and find its root */

    for (i=0; i < ctree->numnodes; i++)
    {
        if (dad[ctree->node[i].comp]!=NIL)
            ctree->node[i].dad = cmap[dad[ctree->node[i].comp]];
        else
        {
            ctree->node[i].dad = NIL;
            ctree->root = i;
        }
    }
    free(dad);

    /* Copy son information to the maxtree */

    nsons = AllocIntArray(ctree->numnodes);
    for (i=0; i < ctree->numnodes; i++)
    {
        p = ctree->node[i].dad;
        if (p != NIL)
        {
            nsons[p]++;
        }
    }
    for (i=0; i < ctree->numnodes; i++)
    {
        if (nsons[i] != 0)
        {
            ctree->node[i].son = AllocIntArray(nsons[i]);
        }
    }
    free(nsons);

    for (i=0; i < ctree->numnodes; i++)
    {
        p = ctree->node[i].dad;
        if (p != NIL)
        {
            ctree->node[p].son[ctree->node[p].numsons]=i;
            ctree->node[p].numsons++;
        }
    }

    /* Compute size of each node */

    for (p=0; p < n; p++)
        ctree->node[cmap[p]].size++;

    return(ctree);
}

void DestroySgCTree(SgCTree **ctree){
    SgCTree *tmp=*ctree;
    int i;

    if (tmp != NULL)
    {
        free(tmp->cmap);
        for (i=0; i < tmp->numnodes; i++)
        {
            if (tmp->node[i].numsons!=0)
                free(tmp->node[i].son);
        }
        free(tmp->node);
        free(tmp);
        *ctree = NULL;
    }
}

int SgAncestor(int *dad, int *cmap, int rq){
    int r,ro;

    ro = r  = dad[rq];
    while (r != NIL)
    {
        ro = r = SgRepresentative(cmap,r);
        r  = dad[r];
    }
    return(ro);
}

int SgRepresentative(int *cmap, int p){
    if (cmap[p]==p)
        return(p);
    else
        return(cmap[p]=SgRepresentative(cmap,cmap[p]));
}


void SgCumSize(SgCTree *ctree, int i){
    int s,j;

    for (j=0; j < ctree->node[i].numsons; j++)
    {
        s = ctree->node[i].son[j];
        SgCumSize(ctree,s);
        ctree->node[i].size = ctree->node[i].size + ctree->node[s].size;
    }
    return;
}

int *SgAreaOpen(Subgraph *g, int thres){
    SgCTree *ctree=NULL;
    int i,p;
    int *fval;
    int *level=NULL;

    ctree = CreateSgMaxTree(g);
    SgCumSize(ctree,ctree->root);
    level = AllocIntArray(ctree->numnodes);
    for (i=0; i < ctree->numnodes; i++)
        level[i]=ctree->node[i].level;

    for (i=0; i < ctree->numnodes; i++)
        if (ctree->node[i].numsons==0)
            level[i]=SgAreaLevel(ctree,level,i,thres);
    fval = AllocIntArray(g->nnodes);
    for (p=0; p < g->nnodes; p++)
        fval[p]=level[ctree->cmap[p]];
    DestroySgCTree(&ctree);
    free(level);
    return(fval);
}

int SgAreaLevel(SgCTree *ctree, int *level, int i, int thres){

    if (i==-1)// passou o pai da raiz
        return(0);

    if ((ctree->node[i].size > thres)||(i==ctree->root))
        return(ctree->node[i].level);
    else
        return(level[i]=SgAreaLevel(ctree,level,ctree->node[i].dad,thres));
}


int SgVolumeLevel(SgCTree *ctree, int *level, int i, int thres, int cumvol){
    int dad,vol=cumvol;

    if (i==-1)// passou o pai da raiz
        return(0);

    dad = ctree->node[i].dad;
    if (dad != NIL)
        vol = cumvol+
              abs(ctree->node[i].level-ctree->node[dad].level)*ctree->node[i].size;

    if ((vol > thres)||(i==ctree->root))
        return(ctree->node[i].level);
    else
        return(level[i]=SgVolumeLevel(ctree,level,dad,thres,vol));
}


int *SgVolumeOpen(Subgraph *g, int thres){
    SgCTree *ctree=NULL;
    int i,p;
    int *fval=NULL;
    int *level=NULL;

    ctree = CreateSgMaxTree(g);
    SgCumSize(ctree,ctree->root);
    level = AllocIntArray(ctree->numnodes);
    for (i=0; i < ctree->numnodes; i++)
        level[i]=ctree->node[i].level;
    for (i=0; i < ctree->numnodes; i++)
        if (ctree->node[i].numsons==0)
            level[i]=SgVolumeLevel(ctree,level,i,thres,0);
    fval = AllocIntArray(g->nnodes);
    for (p=0; p < g->nnodes; p++)
        fval[p]=level[ctree->cmap[p]];
    DestroySgCTree(&ctree);
    free(level);
    return(fval);
}
