#include <stdio.h>
#include <stdlib.h>

#include <utils/buffer.h>

int
main (int argc, char *argv[])
{
	if (argc < 2)
		{
			fprintf (stderr, "Usage: pinky <filename>\n");
			return EXIT_FAILURE;
		}

	char *fname = argv[1];
	FILE *fp = fopen (fname, "r");
	if (!fp)
		{
			fprintf (stderr, "Couldn't open %s\n", fname);
			return EXIT_FAILURE;
		}

	fseek (fp, 0, SEEK_END);
	size_t fsize = ftell (fp);
	fseek (fp, 0, SEEK_SET);

	char buf[fsize + 1];
	fread (buf, fsize, 1, fp);
	buf[fsize] = '\0';

	// TODO: Interpret and compile XDDD

	fclose (fp);
	return EXIT_SUCCESS;
}
