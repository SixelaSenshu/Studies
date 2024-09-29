build:
	gcc question3/suid.c -o suid_c
	gcc question8/rmg_c.c question8/check_pass.c -o rmg_c	
	gcc question9/cryptage.c question9/pwg.c question9/check_pass.c -l:libcrypt.a  -o pwg_c	
	gcc question9/cryptage.c question9/rmg_c.c question9/check_pass.c  -l:libcrypt.a -o rmg_crypt_c
