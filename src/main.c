#include <stdio.h>
#include <stdlib.h>

#include <lexer.h>
#include <token.h>

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
	struct lexer lexer = { 0 };
	lexer_init (buf, &lexer);
	lexer_tokenise (&lexer);
	for (int i = 0; i < lexer.tokens.size; i++)
		{
			struct token *tok = vector_get (i, &lexer.tokens);
			token_print (tok);
		}

	lexer_free (&lexer);

	fclose (fp);
	return EXIT_SUCCESS;
}
