#include "OPF.h"

int main(int argc, char **argv)
{
  fflush(stdout);
  fprintf(stdout, "\nProgram that executes the semi supervised training phase of the OPF classifier\n");
  fprintf(stdout, "\nIf you have any problem, please contact: ");
  fprintf(stdout, "\n- paraguassuec@gmail.com");
  fprintf(stdout, "\n- alexandre.falcao@gmail.com");
  fprintf(stdout, "\n- papa.joaopaulo@gmail.com\n");
  fprintf(stdout, opf_version);
  fprintf(stdout, "\n");
  fflush(stdout);

  if ((argc != 5) && (argc != 4) && (argc != 3) && (argc != 2))
  {
    fprintf(stderr, "\nusage opf_semi_train <P1> <P2>");
    fprintf(stderr, "\nP1: Labeled training set in the OPF file format");
    fprintf(stderr, "\nP2: Unlabeled training set in the OPF file format");
    fprintf(stderr, "\nP3: Evaluation set in the OPF file format");
    fprintf(stderr, "\nP4: Precomputed distance file (leave it in blank if you are not using this resource)\n");
    exit(-1);
  }

  int n, i;
  int opf_ComputeEvaluation = 0;
  char fileName[256];
  FILE *f = NULL;
  timer tic, toc;
  float time;
  Subgraph *geval = NULL;

  if (argc == 4)
    opf_ComputeEvaluation = 1;

  if (argc == 5)
    opf_PrecomputedDistance = 1;

  fprintf(stdout, "\nReading labeled data file...");
  fflush(stdout);
  Subgraph *g = ReadSubgraph(argv[1]);
  fprintf(stdout, " OK");
  fflush(stdout);

  fprintf(stdout, "\nReading unlabeled data file...");
  fflush(stdout);
  Subgraph *gunl = ReadSubgraph(argv[2]);
  fprintf(stdout, " OK");
  fflush(stdout);

  if (opf_ComputeEvaluation)
  {
    fprintf(stdout, "\nReading evaluation data file...");
    fflush(stdout);
    geval = ReadSubgraph(argv[3]);
    fprintf(stdout, " OK");
    fflush(stdout);
  }

  if (opf_PrecomputedDistance)
    opf_DistanceValue = opf_ReadDistances(argv[4], &n);

  fprintf(stdout, "\nTraining Semi OPF classifier ...");
  fflush(stdout);
  gettimeofday(&tic, NULL);
  Subgraph *s = opf_OPFSemiLearning(g, gunl, geval);
  opf_OPFTraining(s);
  gettimeofday(&toc, NULL);
  fprintf(stdout, " OK");
  fflush(stdout);

  fprintf(stdout, "\nWriting classifier's model file ...");
  fflush(stdout);
  opf_WriteModelFile(s, "classifier.opf");
  fprintf(stdout, " OK");
  fflush(stdout);

  fprintf(stdout, "\nWriting output file ...");
  fflush(stdout);
  sprintf(fileName, "%s.out", argv[1]);
  opf_WriteOutputFile(s, fileName);
  fprintf(stdout, " OK");
  fflush(stdout);

  fprintf(stdout, "\nDeallocating memory ...");
  fflush(stdout);
  DestroySubgraph(&s);
  if (opf_PrecomputedDistance)
  {
    for (i = 0; i < n; i++)
      free(opf_DistanceValue[i]);
    free(opf_DistanceValue);
  }
  fprintf(stdout, " OK\n");

  time = ((toc.tv_sec - tic.tv_sec) * 1000.0 + (toc.tv_usec - tic.tv_usec) * 0.001) / 1000.0;
  fprintf(stdout, "\nExecution time: %f seconds\n", time);
  fflush(stdout);

  sprintf(fileName, "%s.time", argv[1]);
  f = fopen(fileName, "a");
  fprintf(f, "%f\n", time);
  fclose(f);

  return 0;
}
