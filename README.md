# SFSD-Project
Simulateur Simplifié d’un Système de Gestion de Fichiers (SGF)
Gestionnaire de Fichiers Simulé

Description :

Ce programme est une simulation en C d’un système de gestion de fichiers.
 Il permet de gérer des enregistrements, des fichiers et leurs métadonnées à l’aide de blocs mémoire simulés. 
 Vous pouvez insérer, rechercher, modifier, supprimer et organiser des enregistrements dans des fichiers.

 Caractéristiques
•Création et gestion de fichiers avec différents modes d’organisation (contigu ou chaîné, trié ou non trié).
•Insertion, modification, suppression et tri des enregistrements.
•Défragmentation et compactage pour optimiser la mémoire.
•Affichage des métadonnées et de l’état du disque.

Pré-requis
•Un compilateur C (ex. : GCC).
•Un système compatible avec les standards C (Linux, macOS, Windows).

1. Menu Principal

Une fois le programme exécuté, un menu interactif s’affiche. Voici les options disponibles :
•Créer un fichier : Configurez un fichier avec des modes d’organisation spécifiques.
•Insérer un enregistrement : Ajoutez des données dans un fichier.
•Afficher un fichier : Consultez les enregistrements et métadonnées d’un fichier.
•Rechercher un enregistrement : Trouvez un enregistrement spécifique par son ID.
•Modifier un enregistrement : Mettez à jour le contenu d’un enregistrement.
•Supprimer un enregistrement : Supprimez un enregistrement d’un fichier.
•Défragmenter la mémoire : Réorganisez les blocs pour éliminer les espaces inutilisés.
•Quitter : Fermez le programme.

2. Instructions Étape par Étape

Création d’un fichier
•Fournissez un nom pour le fichier.
•Choisissez un mode global (contigu ou chaîné).
•Choisissez un mode interne (trié ou non trié).

Insertion d’enregistrements
•Entrez un identifiant unique (ID) et un contenu pour l’enregistrement.
•Répétez l’opération pour ajouter plusieurs enregistrements.

Affichage
•Sélectionnez un fichier pour voir son contenu, ses métadonnées et ses blocs associés.

Recherche et modification
•Saisissez l’ID de l’enregistrement à rechercher ou à modifier.
•Fournissez les nouvelles données en cas de modification.

Suppression
•Saisissez l’ID de l’enregistrement à supprimer.

Organisation des fichiers
•Source : Tous les fichiers source sont dans le répertoire principal.
•Exécutable : Généré après compilation.
•Documentation : Ce fichier README explique les fonctionnalités principales.

Equipe de projet : ce projet a ete realise par :
Al kalla omar 222231376516
Guedouche saadi ahmed 222231486918
Korichi hannane 33383208
Sekkour ishak abdelbarie 222231401311
Salah houdeifa 232331717502
