#include <stdio.h>
#include <stdlib.h>


int main()
{
	// FILE *fout;
	// int i;

	// if((fout = fopen("output.txt", "w")) == NULL)
	// {
	// 	fprintf(stderr, "unable to open output.txt (mode=\"w\")\n");
	// 	return EXIT_FAILURE;
	// }
	// system("gnome-terminal -- tail -f output.txt");
	// while((i = getchar()) != EOF)
	// {
	// 	putc(i, fout);
	// }

	// fclose(fout);

	// return 0 ;

	//gnome-terminal -- tail -f output.txt
	system("gnome-terminal -- tail -f output.txt");

	system("gnome-terminal -- tail -f output2.txt");
}