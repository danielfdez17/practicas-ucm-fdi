#include <stdio.h>
#include <stdlib.h>
#include <err.h>

// getc() --> fread() && putc() --> fwrite()

int main(int argc, char* argv[]) {
	FILE* file = NULL;

	if (argc!=2) {
		fprintf(stderr,"Usage: %s <file_name>\n",argv[0]);
		exit(1);
	}

	/* Open file */
	if ((file = fopen(argv[1], "r")) == NULL)
		err(2,"The input file %s could not be opened", argv[1]);

	/* Read file byte by byte */
	/*while ((c = getc(file)) != EOF) {
		// Print byte to stdout
		ret=putc((unsigned char) c, stdout);
		if (ret == EOF){
			fclose(file);
			err(3,"putc() failed!!\n");
		}
	}//*/
    
	// MODIFICACIONES
	// fwrite(ptr_donde_leer_dato, size_dato, n_bytes, archivo);
	// fread(ptr_donde_guardar_dato, size_dato, n_bytes, archivo);
	char buffer;
	while ((fread(&buffer, sizeof(char), 1, file)) == 1) {
		if (fwrite(&buffer, sizeof(char), 1, stdout) < 1) {
			fclose(file);
			err(3,"fwrite() failed!\n");
		}
	}//*/

	fclose(file);
	return 0;
}
