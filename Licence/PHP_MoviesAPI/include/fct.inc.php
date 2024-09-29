<?php

    function estConnecte(){
        return isset($_SESSION['id']);
    }

    function connecter($id,$nom,$prenom){
        $_SESSION['id']= $id; 
        $_SESSION['nom']= $nom;
	    $_SESSION['prenom']= $prenom;
    }

    function estEntierPositif($valeur) {
        return preg_match("/[^0-9]/", $valeur) == 0;
    }

    function estTableauEntiers($tabEntiers) {
        $ok = true;
        if (isset($unEntier) ){
            foreach($tabEntiers as $unEntier){
                if(!estEntierPositif($unEntier)){
                    $ok=false; 
                }
            }
	    }
	    return $ok;
    }

    function ajouterErreur($msg){
        if (! isset($_REQUEST['erreurs'])){
            $_REQUEST['erreurs']=array();
        }
        $_REQUEST['erreurs'][]=$msg;
    }

    function nbErreurs(){
        if (!isset($_REQUEST['erreurs'])){
            return 0;
        }
        else{
            return count($_REQUEST['erreurs']);
        }
    }

    function input_data($data){
        $data = trim($data);
        $data = stripslashes($data);
        $data = htmlspecialchars($data);
        return $data;
    }

    function generateCode(){
        $numbytes = 3;
        $bytes = openssl_random_pseudo_bytes($numbytes);
        $hex   = bin2hex($bytes);
	return $hex;
    }

    function verif2Strings(string $chaine1, string $chaine2):bool {
        $verification = false;

        if ($chaine1==$chaine2)
        {
            $verification = true;
        }
        return $verification;
    }

    function verifSecuPWP($lePWD):  bool {
        $message=false;
        $patternPassword='#^(?=.*[a-z])(?=.*[A-Z])(?=.*[0-9])(?=.*\W){12,}#';

        if (preg_match($patternPassword, $lePWD)==false){
            echo 'Le mot de passe doit contenir au moins 12 caractères, une majuscule,'
                . ' une minuscule et un caractère spécial<br/>';
            $message=false;
        }
        else{
            $message=true;
        }
        return $message;
    }

    function hashPWD($mdp): string{
        return password_hash($mdp, PASSWORD_DEFAULT);
    }

    function checkPWD($pwd,$pwdBDD) : bool {
        return password_verify($pwd, $pwdBDD);
    }
