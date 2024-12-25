#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

int main() {
  char expression[256];
  if (fgets(expression, sizeof(expression), stdin) == NULL) {
    return 0;
  }
  size_t len = strlen(expression);
  if (len > 0 && expression[len - 1] == '\n') {
    expression[len - 1] = '\0';
  }
  if (strlen(expression) == 0) {
    return 0;
  }
  char *source_filename = "temp_code.c";
  char *executable_filename = "temp_exec";

  FILE *source_file = fopen(source_filename, "w");
  if (!source_file) {
    perror("fopen");
    return 1;
  }
  fprintf(source_file, "#include <stdio.h>\n");
  fprintf(source_file, "int main() {\n");
  fprintf(source_file, "    int result = (%s);\n", expression);
  fprintf(source_file, "    printf(\"%%d\\n\", result);\n");
  fprintf(source_file, "    return 0;\n");
  fprintf(source_file, "}\n");
  fclose(source_file);
  char *gcc_args[] = {"gcc", source_filename, "-o", executable_filename, NULL};
  if (fork() == 0) {
    execvp("gcc", gcc_args);
    perror("exec gcc");
    exit(1);
  } else {
    int status;
    wait(&status);
    if (status != 0) {
      perror("CE");
      exit(1);
    }
  }
  if (fork() == 0) {
    execlp("./temp_exec", "./temp_exec", NULL);
    perror("execlp");
    exit(EXIT_FAILURE);
  } else {
    int status;
    wait(&status);
  }
  unlink(source_filename);
  unlink(executable_filename);
  return 0;
}
