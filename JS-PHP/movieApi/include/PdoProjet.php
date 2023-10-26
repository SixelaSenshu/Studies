<?php

class PdoProjet
{
    private static $pdo;
    private static $api_key_crypt = 'VfrDBgf4+zHIpTnM5FLGS+kQJDiBKJopXSr89AtJoO0lZkRn+E8YkQs4DyR/X9IVxMQ2tx0OkB173/hUpQ/Cmw==';

    private function __construct()
    {
        $dsn = "sqlite:projetphp.db";
        try {
            self::$pdo = new PDO($dsn);
        } catch (PDOException $e) {
            die("Erreur de connexion à la base de données : " . $e->getMessage());
        }
    }

    public static function getPdoPhp()
    {
        if (!self::$pdo) {
            new self();
        }
        return self::$pdo;
    }

    public static function createUserTable($nomTable)
    {
        $pdo = self::getPdoPhp();
        $sql = "CREATE TABLE IF NOT EXISTS $nomTable (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            nom VARCHAR(40) DEFAULT NULL,
            prenom VARCHAR(30) DEFAULT NULL,
            mail VARCHAR(50) DEFAULT NULL,
            motDePasse VARCHAR(250) DEFAULT NULL,
            dateCreation DATETIME DEFAULT CURRENT_TIMESTAMP
        )";
        $pdo->exec($sql);
    }

    public static function createHistoriqueConnexionTable($nomTable)
    {
        $pdo = self::getPdoPhp();
        $sql = "CREATE TABLE IF NOT EXISTS $nomTable (
            idUser INTEGER REFERENCES users(id) ON DELETE CASCADE,
            dateDebutLog DATETIME NOT NULL,
            dateFinLog DATETIME DEFAULT NULL
        )";
        $pdo->exec($sql);
    }

    public static function createRealisateurTable($nomTable)
    {
        $pdo = self::getPdoPhp();
        $sql = "CREATE TABLE IF NOT EXISTS $nomTable (
            idApi INTEGER PRIMARY KEY DEFAULT NULL,
            nomRealisateur VARCHAR(40) DEFAULT NULL,
            prenomRealisateur VARCHAR(30) DEFAULT NULL,
            anneeNaiss DATETIME DEFAULT NULL
        )";
        $pdo->exec($sql);
    }

    public static function createFilmsTable($nomTable)
    {
        $pdo = self::getPdoPhp();
        $sql = "CREATE TABLE IF NOT EXISTS $nomTable (
            idApi INTEGER PRIMARY KEY DEFAULT NULL,
            idRealisateur INTEGER REFERENCES realisateur(id) ON DELETE CASCADE,
            idGenre1 INTEGER DEFAULT NULL REFERENCES genres(idApi) ON DELETE CASCADE,
            idGenre2 INTEGER DEFAULT NULL REFERENCES genres(idApi) ON DELETE CASCADE,
            idGenre3 INTEGER DEFAULT NULL REFERENCES genres(idApi) ON DELETE CASCADE,
            idGenre4 INTEGER DEFAULT NULL REFERENCES genres(idApi) ON DELETE CASCADE,
            nomFilm VARCHAR(40) DEFAULT NULL,
            moyenne INTEGER DEFAULT NULL,
            anneeSortie DATETIME NOT NULL
        )";
        $pdo->exec($sql);
    }

    public static function createNotationTable($nomTable)
    {
        $pdo = self::getPdoPhp();
        $sql = "CREATE TABLE IF NOT EXISTS $nomTable (
            idUser INTEGER REFERENCES user(id) ON DELETE CASCADE,
            idFilm INTEGER REFERENCES films(idApi) ON DELETE CASCADE,
            noteUtilisateur INTEGER DEFAULT NULL,
            commentaire VARCHAR(250) DEFAULT NULL
        )";
        $pdo->exec($sql);
    }

    public static function createGenreTable($nomTable)
    {
        $pdo = self::getPdoPhp();
        $sql = "CREATE TABLE IF NOT EXISTS $nomTable (
        idApi INTEGER PRIMARY KEY DEFAULT NULL,
        genre VARCHAR(150) DEFAULT NULL
        )";
        $pdo->exec($sql);

        $tableCreated = $pdo->query("SELECT COUNT(*) FROM $nomTable")->fetchColumn() == 0;

        if ($tableCreated) {
            $genres_results = self::getListeGenre();
            $pdoStatement = $pdo->prepare("INSERT INTO $nomTable (idApi, genre) VALUES (:genreId, :genre)");
            if ($pdoStatement === false) {
                return false;
            }
            foreach ($genres_results['genres'] as $genre) {
                $bv1 = $genre['id'];
                $bv2 = $genre['name'];
                $pdoStatement->bindParam(":genreId", $bv1);
                $pdoStatement->bindParam(":genre", $bv2);
                $executionOk = $pdoStatement->execute();
                if (!$executionOk) {
                    return false;
                }
            }
        }
        return true;
    }

    public static function tailleChampsMail()
    {
        $pdo = self::getPdoPhp();
        $pdoStatement = $pdo->prepare("PRAGMA table_info(Users)");
        $execution = $pdoStatement->execute();
        while ($row = $pdoStatement->fetch()) {
            if ($row['name'] === 'mail') {
                preg_match('/\d+/', $row['type'], $matches);
                return $matches[0];
            }
        }
        return null;
    }

    public static function creeUser($nom, $prenom, $email, $mdp)
    {
        $pdo = self::getPdoPhp();
        $motdepasse = hashPWD($mdp);
        $pdoStatement = $pdo->prepare("INSERT INTO users(id,nom,prenom,mail,motDePasse,dateCreation) "
            . "VALUES (null, :leNom,:lePrenom ,:leMail, :leMdp, date('now'))");

        if ($pdoStatement === false) {
            return false;
        }

        $bv1 = $pdoStatement->bindParam(':leMail', $email);
        $bv2 = $pdoStatement->bindParam(':leMdp', $motdepasse);
        $bv3 = $pdoStatement->bindParam(':leNom', $nom);
        $bv4 = $pdoStatement->bindParam(':lePrenom', $prenom);
        $execution = $pdoStatement->execute();
        return $execution;
    }

    public static function checkUser($login, $pwd): bool
    {
        $user = false;
        $pdo = self::getPdoPhp();
        $pdoStatement = $pdo->prepare("SELECT motDePasse FROM users WHERE mail= :login");
        if ($pdoStatement === false) {
            return false;
        }
        $bvc1 = $pdoStatement->bindParam(':login', $login, PDO::PARAM_STR);
        if ($pdoStatement->execute()) {
            $unUser = $pdoStatement->fetch();
            if (is_array($unUser)) {
                if (count($unUser) != 1) {
                    if (checkPWD($pwd, $unUser['motDePasse'])) {
                        $user = true;
                    }
                } else {
                    throw new Exception("erreur dans la requète");
                }
            }
        }
        return $user;
    }

    public static function connexionInitiale($mail)
    {
        $pdo = self::getPdoPhp();
        $user = self::donneLeUserByMail($mail);
        $id = $user['id'];
        self::ajouteConnexionInitiale($id);
    }

    public static function donneLeUserByMail($login)
    {

        $pdo = self::getPdoPhp();
        $pdoStatement = $pdo->prepare("SELECT id, nom, prenom,mail FROM users WHERE mail= :login");
        if ($pdoStatement === false) {
            return false;
        }
        $bvc1 = $pdoStatement->bindParam(':login', $login, PDO::PARAM_STR);
        if ($pdoStatement->execute()) {
            $unUser = $pdoStatement->fetch();
        } else
            throw new Exception("erreur dans la requête");
        return $unUser;
    }

    public static function ajouteConnexionInitiale($id)
    {
        $pdo = self::getPdoPhp();
        $pdoStatement = $pdo->prepare("INSERT INTO historiqueconnexion "
            . "VALUES (:leUser, date('now'), date('now'))");
        if ($pdoStatement === false) {
            return false;
        }
        $bv1 = $pdoStatement->bindParam(':leUser', $id);
        $execution = $pdoStatement->execute();
        return $execution;
    }

    public static function ajouteConnexion($id)
    {
        $pdo = self::getPdoPhp();
        $pdoStatement = $pdo->prepare("INSERT INTO historiqueconnexion(idUser ,dateDebutLog,dateFinLog) VALUES (?, date('now'), null)");
        if ($pdoStatement === false) {
            return false;
        }
        $bv2 = $pdoStatement->bindParam(1, $id);
        $execution = $pdoStatement->execute();
        return $execution;
    }

    public static function ajouteDeconnexion($id)
    {
        $pdo = self::getPdoPhp();
        $pdoStatement = $pdo->prepare("UPDATE historiqueconnexion SET dateFinLog = date('now') WHERE dateFinLog IS NULL AND idUser = ?");
        if ($pdoStatement === false) {
            return false;
        }
        $bv2 = $pdoStatement->bindParam(1, $id);
        $execution = $pdoStatement->execute();
        return $execution;
    }

    public static function modifNomPrenom($nom, $prenom, $id)
    {
        $pdo = self::getPdoPhp();
        $pdoStatement = $pdo->prepare("UPDATE users SET nom=:leNom, prenom=:lePrenom WHERE id=:id");
        if ($pdoStatement === false) {
            return false;
        }
        $bv1 = $pdoStatement->bindParam(":leNom", $nom);
        $bv2 = $pdoStatement->bindParam(":lePrenom", $prenom);
        $bv3 = $pdoStatement->bindParam(":id", $id);
        $executionOk = $pdoStatement->execute();
        $resultatRequete = $pdoStatement->fetch();
        return $executionOk;
    }

    public static function modifNomPrenomMdp($nom, $prenom, $mdp, $id)
    {
        $hashmdp = hashPWD($mdp);
        $pdo = self::getPdoPhp();
        $pdoStatement = $pdo->prepare("UPDATE users SET nom=:leNom, prenom=:lePrenom,motDePasse=:leMdp WHERE id=:id");
        if ($pdoStatement === false) {
            return false;
        }
        $bv1 = $pdoStatement->bindParam(":leNom", $nom);
        $bv2 = $pdoStatement->bindParam(":lePrenom", $prenom);
        $bv3 = $pdoStatement->bindParam(":leMdp", $hashmdp);
        $bv4 = $pdoStatement->bindParam(":id", $id);
        $executionOk = $pdoStatement->execute();
        return $executionOk;
    }

    public static function SupprimerCompte($id)
    {
        $pdo = self::getPdoPhp();
        $pdoStatement = $pdo->prepare("DELETE FROM users WHERE id=:id");
        if ($pdoStatement === false) {
            return false;
        }
        $bv = $pdoStatement->bindParam(":id", $id);
        $executionOk = $pdoStatement->execute();
        return $executionOk;
    }

    public static function decrypt_api_key($encrypted_key)
    {
        $encryption_key = '0123456789abcdefghijklmnopqrstuvwxyz';
        $data = base64_decode($encrypted_key);
        $iv = substr($data, 0, 16);
        $encrypted = substr($data, 16);
        return openssl_decrypt($encrypted, 'AES-256-CBC', $encryption_key, OPENSSL_RAW_DATA, $iv);
    }

    public static function getListeGenre()
    {
        $api_key = self::decrypt_api_key(self::$api_key_crypt);
        $base_url = 'https://api.themoviedb.org/3/';
        $genres_url = $base_url . 'genre/movie/list?api_key=' . $api_key;
        $genres_results = file_get_contents($genres_url);
        $genres_results = json_decode($genres_results, true);

        return $genres_results;
    }

    public static function afficheInfoFilm($id)
    {
        $api_key = self::decrypt_api_key(self::$api_key_crypt);
        $base_url = 'https://api.themoviedb.org/3/';
        $url = $base_url . 'movie/' . $id . '?api_key=' . $api_key;

        $search_results = file_get_contents($url);
        $search_results = json_decode($search_results, true);

        if (isset($search_results['status_code'])) {
            echo '<center>';
            echo '<h3 style="color:red; text-align:center;">';
            echo 'Aucun résultat trouvé pour le film cherché';
            echo '</h3>';
            echo '</center>';
        } else {

            $idFilm = $search_results['id'];

            $poster_path = 'https://image.tmdb.org/t/p/w500' . $search_results['poster_path'];
            $title = $search_results['title'];
            $release_date = date('d/m/Y', strtotime($search_results['release_date']));
            $overview = $search_results['overview'];
            $vote_average = $search_results['vote_average'];
            $vote_count = $search_results['vote_count'];

            $genre_ids = $search_results['genres'];
            $idGenre1 = isset($genre_ids[0]['id']) ? $genre_ids[0]['id'] : null;
            $idGenre2 = isset($genre_ids[1]['id']) ? $genre_ids[1]['id'] : null;
            $idGenre3 = isset($genre_ids[2]['id']) ? $genre_ids[2]['id'] : null;
            $idGenre4 = isset($genre_ids[3]['id']) ? $genre_ids[3]['id'] : null;

            echo '<div class="box">';
            echo '<div class="box-header">';
            echo '<div class="box-header-image">';
            echo '<img src="' . $poster_path . '" alt="' . $title . '">';
            echo '</div>';
            echo '<div class="box-header-informations">';
            echo '<h1>' . $title . '</h1>';
            echo '<br>';
            echo '<p><strong><u>Date de sortie :</u></strong> ' . $release_date . '</p>';
            echo '<p><strong><u>Note :</u></strong> ' . $vote_average . ' / 10 (' . $vote_count . ' votes)</p>';
            echo '</div>';
            echo '</div>';
            echo '<div class="box-content">';
            echo '<div class="box-content-syn">';
            echo '<h1><u> Synopsis </u></h1>';
            echo '<p>' . $overview . '</p>';
            echo '</div>';
            echo '<div class="box-content-list-actors">';
            echo '<h1><strong><u>Acteurs </u></strong></h1>';

            $acteurs_url = $base_url . 'movie/' . $idFilm . '/credits?api_key=' . $api_key;
            $acteurs_results = file_get_contents($acteurs_url);
            $acteurs_results = json_decode($acteurs_results, true);
            $casting = $acteurs_results['cast'];

            $i = 0;
            $default_image = 'images/unknown.jfif';
            echo '<div class="actors-container">';
            echo '<div class="actors-row">';
            foreach ($casting as $actor) {
                $actor_name = $actor['name'];
                $actor_profile_path = 'https://image.tmdb.org/t/p/w500' . $actor['profile_path'];
                if ($actor['profile_path'] == null) {
                    $actor_profile_path = $default_image;
                }
                echo '<div class="actors-col">';
                echo '<img src="' . $actor_profile_path . '" alt="' . $actor_name . '" style="width: 100px; height: 150px; object-fit: cover;">';
                echo '<p style="margin-top: 5px; font-size: 16px;">' . $actor_name . '</p>';
                echo '</div>';
                $i++;
                if ($i % 5 == 0) {
                    echo '</div><div class="actors-row">';
                }
            }
            echo '</div>';

            $crew_url = $base_url . 'movie/' . $idFilm . '/credits?api_key=' . $api_key;
            $crew_results = file_get_contents($crew_url);
            $crew_results = json_decode($crew_results, true);
            $crew = $crew_results['crew'];

            $director_name = '';
            $director_id = '';
            foreach ($crew as $member) {
                if ($member['job'] == 'Director') {
                    $director_name = $member['name'];
                    $director_id = $member['id'];
                    $director_parts = explode(" ", $director_name);
                    $director_lastname = array_pop($director_parts);
                    $director_firstname = implode(" ", $director_parts);
                    $director_url = $base_url . 'person/' . $director_id . '?api_key=' . $api_key;
                    $director_results = file_get_contents($director_url);
                    $director_results = json_decode($director_results, true);
                    $director_birthyear = substr($director_results['birthday'], 0, 4);
                }
            }

            $_SESSION['movieToAdd'] = array(
                'idFilm' => $idFilm,
                'director_id' => $director_id,
                'director_lastname' => $director_lastname,
                'director_firstname' => $director_firstname,
                'director_birthyear' => $director_birthyear,
                'idGenre1' => $idGenre1,
                'idGenre2' => $idGenre2,
                'idGenre3' => $idGenre3,
                'idGenre4' => $idGenre4,
                'title' => $title,
                'release_date' => $release_date
            );

            echo '</div>';
            echo '</div>';
            echo "<a href=\"index.php?uc=api&action=noterLeFilm&idFilm=$idFilm\">Noter le film</a>";
            echo '</div>';
            echo '</div>';
        }
    }

    public static function recherche($type, $param)
    {
        $api_key = self::decrypt_api_key(self::$api_key_crypt);
        $base_url = 'https://api.themoviedb.org/3/';

        switch ($type) {
            case 'name': {
                    $url = $base_url . 'search/movie?api_key=' . $api_key . '&query=' . urlencode($param) . '&language=fr-FR';

                    $search_results = file_get_contents($url);
                    $search_results = json_decode($search_results, true);

                    if ($search_results['total_results'] > 0) {
                        if ($search_results['total_results'] > 1) {
                            foreach ($search_results['results'] as $movie) {

                                $idFilm = $movie['id'];
                                $poster_path = 'https://image.tmdb.org/t/p/w500' . $movie['poster_path'];
                                $title = $movie['title'];
                                $release_date = date('d/m/Y', strtotime($movie['release_date']));
                                $overview = $movie['overview'];
                                $vote_average = $movie['vote_average'];
                                $vote_count = $movie['vote_count'];

                                echo '<div class="box">';
                                echo '<div class="box-header">';
                                echo '<div class="box-header-image">';
                                echo '<img src="' . $poster_path . '" alt="' . $title . '">';
                                echo '</div>';
                                echo '<div class="box-header-informations">';
                                echo '<h1>' . $title . '</h1>';
                                echo '<br>';
                                echo '<p><strong><u>Date de sortie :</u></strong> ' . $release_date . '</p>';
                                echo '<p><strong><u>Note :</u></strong> ' . $vote_average . ' / 10 (' . $vote_count . ' votes)</p>';
                                echo '</div>';
                                echo '</div>';
                                echo '<div class="box-content">';
                                echo '<div class="box-content-syn">';
                                echo '<h1><u> Synopsis </u></h1>';
                                echo '<p>' . $overview . '</p>';
                                echo '</div>';
                                echo '<p><a href="index.php?uc=api&action=afficheRecherche&idFilm=' . $idFilm . '"> Voir les infos du film </a></p>';
                                echo '</div>';
                                echo '</div>';
                            }
                        } else {
                            $id = $search_results['results'][0]['id'];
                            self::afficheInfoFilm($id);
                        }
                    } else {
                        echo '<center>';
                        echo '<h3 style="color:red; text-align:center;">';
                        echo 'Aucun résultat trouvé pour "' . $param . '"';
                        echo '</h3>';
                        echo '</center>';
                    }
                    break;
                }

            case 'actor': {
                    $url = $base_url . 'search/person?api_key=' . $api_key . '&query=' . urlencode($param) . '&language=fr-FR';
                    $search_results = file_get_contents($url);
                    $search_results = json_decode($search_results, true);

                    if (!empty($search_results['results'])) {
                        $actor_id = $search_results['results'][0]['id'];

                        $actor_info_url = $base_url . 'person/' . $actor_id . '?api_key=' . $api_key . '&language=fr-FR';
                        $actor_info = file_get_contents($actor_info_url);
                        $actor_info = json_decode($actor_info);

                        echo '<div class="box">';
                        echo '<div class="box-header">';
                        echo '<div class="box-header-image">';
                        echo '<img src="https://image.tmdb.org/t/p/w300' . $actor_info->profile_path . '">';
                        echo '</div>';
                        echo '<div class="box-header-informations">';
                        echo '<h1>' . $actor_info->name . '</h1>';
                        echo '</div>';
                        echo '</div>';
                        echo '<div class="box-content">';
                        echo '<div class="box-content-syn">';
                        echo '<h1><u>' . "Biographie" . '</u></h1>';
                        echo '<p>' . $actor_info->biography . '</p>';
                        echo '</div>';
                        echo '<div class="box-content-list-actors">';
                        echo '<h1><strong><u>Films </u></strong></h1>';
                        echo '<br>';

                        $movies = $base_url . 'person/' . $actor_id . '/movie_credits?api_key=' . $api_key . '&language=fr-FR';
                        $movies = file_get_contents($movies);
                        $movies = json_decode($movies);
                        $default_image = 'images/unknown2.png';
                        $i = 0;
                        echo '<div class="movies-container">';
                        echo '<div class="movies-row">';
                        foreach ($movies->cast as $movie) {
                            $movie_title = $movie->title;
                            $movie_poster_path = 'https://image.tmdb.org/t/p/w500' . $movie->poster_path;
                            if ($movie->poster_path == null) {
                                $movie_poster_path = $default_image;
                            }
                            echo '<div class="movies-col">';
                            echo '<img src="' . $movie_poster_path . '" alt="' . $movie_title . '" style="width: 100px; height: 150px; object-fit: cover;">';
                            echo '<p style="margin-top: 5px; font-size: 16px;">' . $movie_title . '</p>';
                            echo '</div>';
                            $i++;
                            if ($i % 5 == 0) {
                                echo '</div><div class="movies-row">';
                            }
                        }
                        echo '</div>';
                        echo '</div>';
                        echo '</div>';
                        echo '</div>';
                        echo '</div>';
                    } else {
                        echo '<center>';
                        echo '<h3 style="color:red; text-align:center;">';
                        echo 'Aucun résultat trouvé pour "' . $param . '"';
                        echo '</h3>';
                        echo '</center>';
                    }
                    break;
                }

            case 'genre': {
                    $genres_results = self::getListeGenre();
                    $genre_id = null;
                    foreach ($genres_results['genres'] as $genre) {
                        if ($genre['id'] == $param) {
                            $genre_id = $genre['id'];
                        }
                    }

                    $config_url = $base_url . 'configuration?api_key=' . $api_key;
                    $config_results = file_get_contents($config_url);
                    $config_results = json_decode($config_results, true);
                    $base_image_url = $config_results['images']['secure_base_url'] . $config_results['images']['poster_sizes'][3];

                    $page = isset($_GET['page']) ? intval($_GET['page']) : 1;
                    $url = $base_url . 'discover/movie?api_key=' . $api_key . '&with_genres=' . $genre_id . '&page=' . $page . '&language=fr-FR';
                    $search_results = file_get_contents($url);
                    $search_results = json_decode($search_results);

                    foreach ($search_results->results as $movie) {
                        $poster_url = $base_image_url . $movie->poster_path;

                        echo '<div class="box">';
                        echo '<div class="box-header">';
                        echo '<div class="box-header-image">';
                        echo '<img src="' . $poster_url . '" alt="' . $movie->title . '">';
                        echo '</div>';
                        echo '<div class="box-header-informations">';
                        echo '<h1>' . $movie->title . '</h1>';
                        echo '<br>';
                        echo '<p><strong><u>Date de sortie :</u></strong> ' . $movie->release_date . '</p>';
                        echo '<p><strong><u>Note :</u></strong> ' . $movie->vote_average . ' / 10 (' . $movie->vote_count . ' votes)</p>';
                        echo '</div>';
                        echo '</div>';
                        echo '<div class="box-content">';
                        echo '<div class="box-content-syn">';
                        echo '<h1><u> Synopsis </u></h1>';
                        echo '<p>' . $movie->overview . '</p>';
                        echo '</div>';
                        echo '<p><a href="index.php?uc=api&action=afficheRecherche&idFilm=' . $movie->id . '"> Voir les infos du film </a></p>';
                        echo '</div>';
                        echo '</div>';
                    }

                    echo '<div class="box">';
                    echo '<div class="box-headers">';
                    echo '<div class="pagination">';
                    if ($page > 1) {
                        echo '<a href="index.php?uc=api&action=recherche&critereRecherche=' . $type . '&paramRecherche=' . $genre_id . '&page=' . ($page - 1) . '">Page précédente</a>';
                    }
                    echo '<span>Page ' . $page . ' sur ' . $search_results->total_pages . '</span>';
                    if ($page < $search_results->total_pages && $page != 500) {
                        echo '<a href="index.php?uc=api&action=recherche&critereRecherche=' . $type . '&paramRecherche=' . $genre_id . '&page=' . ($page + 1) . '"> Page suivante</a>';
                    }

                    echo '<form method="get" action="index.php?uc=api&action=recherche&critereRecherche=' . $type . '&paramRecherche=' . $genre_id . '&page=' . $_GET['page'] . '">';
                    echo '<input type="hidden" name="uc" value="api">';
                    echo '<input type="hidden" name="action" value="recherche">';
                    echo '<input type="hidden" name="paramRecherche" value="' . $genre_id . '">';
                    echo '<input type="hidden" name="critereRecherche" value="' . $type . '">';
                    echo '<label for="page">Aller à la page :  </label>';
                    echo '<input type="number" name="page" id="page" min="1" max="' . $search_results->total_pages . '" value="' . $page . '">';
                    if ($_GET['page'] = 500) {
                        echo '<br><span style="color:red;">Attention : la limite de pages est de 500 pour cette API.</span>';
                    } else {
                        echo '<button type="submit"> Aller</button>';
                    }
                    echo '</form>';
                    echo '</div>';

                    echo '</div>';
                    echo '</div>';
                    break;
                }
        }
    }

    public static function checkNotation($id, $idFilm)
    {
        $pdo = self::getPdoPhp();
        $pdoStatement = $pdo->prepare('SELECT * FROM notation WHERE idUser = :id AND idFilm = :idFilm');
        if ($pdoStatement === false) {
            return false;
        }
        $bv1 = $pdoStatement->bindParam(':id', $id);
        $bv2 = $pdoStatement->bindParam(':idFilm', $idFilm);
        $execution = $pdoStatement->execute();
        if ($execution) {
            $result = $pdoStatement->fetch();
            return $result;
        }
        return $execution;
    }

    public static function ajouteNotation($id, $idFilm, $note, $commentaire)
    {
        $pdo = self::getPdoPhp();
        $safecommentaire = htmlspecialchars($commentaire);
        $pdoStatement = $pdo->prepare('INSERT INTO notation (idUser, idFilm, noteUtilisateur, commentaire) VALUES (:id, :idFilm, :note, :commentaire)');
        if ($pdoStatement === false) {
            return false;
        }
        $pdoStatement->bindParam(':id', $id);
        $pdoStatement->bindParam(':idFilm', $idFilm);
        $pdoStatement->bindParam(':note', $note);
        $pdoStatement->bindParam(':commentaire', $safecommentaire);
        $execution = $pdoStatement->execute();
        return $execution;
    }

    public static function modifieNotation($id, $idFilm, $note, $commentaire)
    {
        $pdo = self::getPdoPhp();
        $pdoStatement = $pdo->prepare('UPDATE notation SET noteUtilisateur = :note, commentaire = :commentaire WHERE idUser = :id AND idFilm = :idFilm');
        if ($pdoStatement === false) {
            return false;
        }
        $pdoStatement->bindParam(':id', $id);
        $pdoStatement->bindParam(':idFilm', $idFilm);
        $pdoStatement->bindParam(':note', $note);
        $pdoStatement->bindParam(':commentaire', $commentaire);
        $execution = $pdoStatement->execute();
        return $execution;
    }

    public static function checkRealisateur($idApi)
    {
        $pdo = self::getPdoPhp();
        $sql = "SELECT COUNT(*) FROM realisateur WHERE idApi = :idApi";
        $pdoStatement = $pdo->prepare($sql);
        if ($pdoStatement === false) {
            return false;
        }
        $pdoStatement->bindParam(":idApi", $idApi);
        $executionOk = $pdoStatement->execute();
        if (!$executionOk) {
            return false;
        }
        $resultat = $pdoStatement->fetch();

        return $resultat[0] > 0;
    }

    public static function addRealisateur($idApi, $nomRealisateur, $prenomRealisateur, $anneeNaiss)
    {
        if (self::checkRealisateur($idApi)) {
            return true;
        }

        $pdo = self::getPdoPhp();
        $sql = "INSERT INTO realisateur (idApi, nomRealisateur, prenomRealisateur, anneeNaiss) VALUES (:idApi, :nomRealisateur, :prenomRealisateur, :anneeNaiss)";
        $pdoStatement = $pdo->prepare($sql);
        if ($pdoStatement === false) {
            return false;
        }
        $pdoStatement->bindParam(":idApi", $idApi);
        $pdoStatement->bindParam(":nomRealisateur", $nomRealisateur);
        $pdoStatement->bindParam(":prenomRealisateur", $prenomRealisateur);
        $pdoStatement->bindParam(":anneeNaiss", $anneeNaiss);
        $executionOk = $pdoStatement->execute();
        if (!$executionOk) {
            return false;
        }

        return true;
    }

    public static function checkFilm($idApi)
    {
        $pdo = self::getPdoPhp();
        $sql = "SELECT COUNT(*) FROM films WHERE idApi = :idApi";
        $pdoStatement = $pdo->prepare($sql);
        if ($pdoStatement === false) {
            return false;
        }
        $pdoStatement->bindParam(":idApi", $idApi);
        $executionOk = $pdoStatement->execute();
        if (!$executionOk) {
            return false;
        }
        $resultat = $pdoStatement->fetch();

        return $resultat[0] > 0;
    }

    public static function addFilm($idApi, $idRealisateur, $idGenre1, $idGenre2, $idGenre3, $idGenre4, $nomFilm, $anneeSortie)
    {
        if (self::checkFilm($idApi)) {
            return true;
        }

        $pdo = self::getPdoPhp();
        $sql = "INSERT INTO films (idApi, idRealisateur, idGenre1, idGenre2, idGenre3, idGenre4, nomFilm, anneeSortie) VALUES (:idApi, :idRealisateur, :idGenre1, :idGenre2, :idGenre3, :idGenre4, :nomFilm, :anneeSortie)";
        $pdoStatement = $pdo->prepare($sql);
        if ($pdoStatement === false) {
            return false;
        }
        $pdoStatement->bindParam(":idApi", $idApi);
        $pdoStatement->bindParam(":idRealisateur", $idRealisateur);
        $pdoStatement->bindParam(":idGenre1", $idGenre1);
        $pdoStatement->bindParam(":idGenre2", $idGenre2);
        $pdoStatement->bindParam(":idGenre3", $idGenre3);
        $pdoStatement->bindParam(":idGenre4", $idGenre4);
        $pdoStatement->bindParam(":nomFilm", $nomFilm);
        $pdoStatement->bindParam(":anneeSortie", $anneeSortie);
        $executionOk = $pdoStatement->execute();
        if (!$executionOk) {
            return false;
        }

        return true;
    }

    public static function updateFilmMoyenne($idFilm)
    {
        $pdo = self::getPdoPhp();
        $sql = "UPDATE films SET moyenne = (SELECT AVG(noteUtilisateur) FROM notation WHERE idFilm = :idFilm) WHERE idApi = :idFilm";
        $stmt = $pdo->prepare($sql);
        $stmt->bindParam(':idFilm', $idFilm);
        $execution = $stmt->execute();
        return $execution;
    }

    public static function getListeFilmsNotesUtilisateur($idUser, $tri, $ordre, $genre, $annee, $realisateur)
    {
        $pdo = self::getPdoPhp();

        $requete = "SELECT films.nomFilm,
        realisateur.nomRealisateur || ' ' || realisateur.prenomRealisateur AS realisateur,
        substr(films.anneeSortie, 7, 4) AS anneeSortie,
        group_concat(genres.genre, ', ') AS genres,
        notation.noteUtilisateur,
        notation.commentaire
        FROM films
        JOIN notation ON films.idApi = notation.idFilm
        LEFT JOIN realisateur ON films.idRealisateur = realisateur.idApi
        LEFT JOIN genres ON films.idGenre1 = genres.idApi OR films.idGenre2 = genres.idApi OR films.idGenre3 = genres.idApi OR films.idGenre4 = genres.idApi";

        if (!empty($genre)) {
            $requete .= " JOIN genres AS g ON (films.idGenre1 = g.idApi OR films.idGenre2 = g.idApi OR films.idGenre3 = g.idApi OR films.idGenre4 = g.idApi) AND g.genre = :genre";
        }

        if (!empty($realisateur)) {
            $requete .= " JOIN realisateur AS r ON films.idRealisateur = r.idApi AND (r.nomRealisateur || ' ' || r.prenomRealisateur) = :realisateur";
        }

        $requete .= " WHERE notation.idUser = :idUser";

        if (!empty($annee)) {
            $requete .= " AND substr(films.anneeSortie, 7, 4) = :annee";
        }

        $requete .= " GROUP BY films.nomFilm";

        if (!empty($tri)) {
            $requete .= " ORDER BY $tri $ordre";
        }

        $stmt = $pdo->prepare($requete);
        $stmt->bindParam(':idUser', $idUser);

        if (!empty($genre)) {
            $stmt->bindParam(':genre', $genre);
        }

        if (!empty($annee)) {
            $stmt->bindParam(':annee', $annee);
        }

        if (!empty($realisateur)) {
            $stmt->bindParam(':realisateur', $realisateur);
        }

        $stmt->execute();
        $resultat = $stmt->fetchAll(PDO::FETCH_ASSOC);

        $tableauHtml = '<div class="table"><table><thead><tr><th>Nom du film</th><th>Réalisateur</th><th>Année de sortie</th><th>Genres</th><th>Note</th><th>Commentaire</th></tr></thead><tbody>';
        foreach ($resultat as $filmNote) {
            $tableauHtml .= '<tr><td>' . $filmNote['nomFilm'] . '</td><td>' . $filmNote['realisateur'] . '</td><td>' . $filmNote['anneeSortie'] . '</td><td>' . $filmNote['genres'] . '</td><td>' . $filmNote['noteUtilisateur'] . '</td><td>' . htmlspecialchars($filmNote['commentaire']) . '</td></tr>';
        }
        $tableauHtml .= '</tbody></table></div>';
        return $tableauHtml;
    }

    public static function getListeGenresFilmsNotesUtilisateur($idUser)
    {
        $pdo = self::getPdoPhp();
        $stmt = $pdo->prepare("SELECT DISTINCT genres.genre AS genre
                        FROM films
                        JOIN notation ON films.idApi = notation.idFilm
                        JOIN genres ON films.idGenre1 = genres.idApi OR films.idGenre2 = genres.idApi OR films.idGenre3 = genres.idApi OR films.idGenre4 = genres.idApi
                        WHERE notation.idUser = :idUser");
        $stmt->bindParam(':idUser', $idUser);
        $stmt->execute();
        $resultat = $stmt->fetchAll(PDO::FETCH_ASSOC);

        $listeGenres = [];
        foreach ($resultat as $row) {
            array_push($listeGenres, $row['genre']);
        }
        return $listeGenres;
    }

    public static function getListeRealisateursFilmsNotesUtilisateur($idUser)
    {
        $pdo = self::getPdoPhp();
        $stmt = $pdo->prepare("SELECT DISTINCT realisateur.nomRealisateur || ' ' || realisateur.prenomRealisateur AS realisateur
                            FROM films
                            JOIN notation ON films.idApi = notation.idFilm
                            JOIN realisateur ON films.idRealisateur = realisateur.idApi
                            WHERE notation.idUser = :idUser");
        $stmt->bindParam(':idUser', $idUser);
        $stmt->execute();
        $resultat = $stmt->fetchAll(PDO::FETCH_ASSOC);

        $listeRealisateurs = [];
        foreach ($resultat as $row) {
            array_push($listeRealisateurs, $row['realisateur']);
        }
        return $listeRealisateurs;
    }

    public static function getListeAnneesSortieFilmsNotesUtilisateur($idUser)
    {
        $pdo = self::getPdoPhp();
        $stmt = $pdo->prepare("SELECT DISTINCT substr(films.anneeSortie, 7, 4) AS anneeSortie
                            FROM films
                            JOIN notation ON films.idApi = notation.idFilm
                            WHERE notation.idUser = :idUser
                            ORDER BY anneesortie");
        $stmt->bindParam(':idUser', $idUser);
        $stmt->execute();
        $resultat = $stmt->fetchAll();

        $listeAnneesSortie = [];
        foreach ($resultat as $row) {
            array_push($listeAnneesSortie, $row['anneeSortie']);
        }
        return $listeAnneesSortie;
    }
}
