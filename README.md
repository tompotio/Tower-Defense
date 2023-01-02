# Tower Defense

## Description

* Les fonctions SDL

Les fonctions de SDL sont automatisées/wrappées par de nouvelles fonctions, dans les différentes classes cf. : RenderClean, AddTexture etc.

* Les commentaires

Si par exemple il n'y a pas beaucoup de commentaires dans le main, c'est parce que les fonctions appelées sont déjà commentées dans leur header respectif.
Il suffit donc de passer la souris dessus pour afficher une description (marche sous VS code, sinon lire dans le .hpp).

## Getting Started

### Dependencies


* cmake
* SDL2
* SDL2_image 
* SDL2_mixer
* SDL2_ttf


### Installing

* Any modifications needed to be made to files/folders

- Pour lancer le jeu la première fois :

```
    mkdir build
    cd build
    cmake ..
    make
```

### Executing program

* Pour lancer le programme, il faut taper
```
   ./Tower Defense
```

## Help

Comment jouer
```
    Le but du jeu est de défendre sa base contre les ennemis.
    Afin de se défendre il faut placer des tours sur la carte.
    Pour se faire il suffit de cliquer sur une des tours et de la positionner sur la carte en maintenant le clic gauche enfoncé.

```

Commandes du jeu
```
    Pour afficher les détails visuels clic droit.
    Les détails visuels ne s'affichent pas directement, après avoir clic droit, il suffit d'appuyer sur les touches : 
        G : Affiche la grille du jeu
        E : Affiche la hitbox des ennemis
        F : Affiche les FPS
        K : Maintenir la lettre appuyée et cliquer sur l'endroit où l'on souhaite générer un chemin de test
        (C'est un chemin pour faire la démo du système de pathfinding *A, attention, le chemin ne se génère que sur les routes des ennemis)
```

## Authors

Tompotio - CLEMENT Aïssa

Vopexx - HADIBI Neil

## Version History

