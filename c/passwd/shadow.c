#include <stdio.h>
#include <stdlib.h>
#include <pwd.h>
#include <shadow.h>

/*
 *  * Print information from the password entry
 *   * about the user name given as argv[1].
 *    */

int main( int argc, char** argv ) 
{
	struct spwd* sp; 
	if (argc < 2) 
	{
		printf("%s username \n", argv[0]);
		return(EXIT_FAILURE);
	}

	if( ( sp = getspnam( argv[1] ) ) == (struct spwd*)0) 
	{
		fprintf( stderr, "getspnam: unknown %s\n", argv[1] );
		return( EXIT_FAILURE );
	}
	printf( "login name  %s\n", sp->sp_namp );
	printf( "password    %s\n", sp->sp_pwdp );
	printf( "last password change    %ld\n", sp->sp_lstchg );
	printf( "days until change allowed    %d\n", sp->sp_min );
	printf( "days before change required    %d\n", sp->sp_max );
	printf( "days warning for expiration    %d\n", sp->sp_warn );
	printf( "days before account inactive    %d\n", sp->sp_inact );
	printf( "date when account expires    %d\n", sp->sp_expire );
	printf( "reserved for future use    %d\n", sp->sp_flag ); 

	return( EXIT_SUCCESS );
}
