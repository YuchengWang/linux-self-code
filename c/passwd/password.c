#include <grp.h>
#include <pwd.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int main (void)
{
	uid_t me;
	struct passwd *my_passwd;

	/* Get information about the user ID.  */
	me = getuid ();
	my_passwd = getpwuid (me);
	if (!my_passwd)
	{
		printf ("Couldn't find out about user %d.\n", (int) me);
		exit (EXIT_FAILURE);
	}

	/* Print the information.  */
	printf ("My login name is %s.\n", my_passwd->pw_name);
	printf ("My passwd is %s.\n", my_passwd->pw_passwd);
	printf ("My uid is %d.\n", (int) (my_passwd->pw_uid));
	printf ("My gid is %d.\n", (int) (my_passwd->pw_gid));
	printf ("My Real name is %s.\n", my_passwd->pw_gecos);
	printf ("My home directory is %s.\n", my_passwd->pw_dir);
	printf ("My default shell is %s.\n", my_passwd->pw_shell);

	return EXIT_SUCCESS;
}
