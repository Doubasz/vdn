# Vent du Nord

## Description du projet

Le projet **"Vent du Nord"** est un jeu de plateforme en 2D qui suit le voyage de **Zawali**, un personnage traversant le désert pour atteindre une ville. Ce jeu propose une expérience immersive en pixel art inspirée des paysages et cultures du désert.

### Contexte

Le projet est développé de manière autonome dans le cadre d'un apprentissage personnel et universitaire (*LIFAPCD - Licence 2 Informatique Lyon 1*).

### Origine de l'idée

Ce projet est né d'une volonté de mettre en avant la diversité des paysages désertiques, tout en perfectionnant les compétences en programmation et en game design.

---

## Description de la demande

### Résultats attendus

- Un jeu jouable sur PC (*Windows/Linux*).
- Un gameplay fluide en **60 FPS**.
- Une progression à travers **2 niveaux distincts** :
  1. **Désert avec des vibes de mine**
  2. **Forêt**
- Un jeu accessible à tous et facile à jouer pour le moment.
- Des bruitages bien travaillés et une musique adaptée à chaque niveau.
- Un design pixel art qui capture l'essence des environnements désertiques et forestiers.

### Fonctionnalités du produit

#### 🎮 Gameplay

- **Déplacements :**
  - **Q / D** (ou **Flèche gauche / Flèche droite**) pour bouger.
  - **Espace** pour sauter.
  - **A** (AZERTY) pour frapper.
  - **Echap** pour mettre en pause.
- **Système de vies :**
  - Perte d'une vie à chaque mort.
  - Retour au début du niveau si toutes les vies sont perdues.
- **Objectif :** Atteindre la fin de chaque niveau sans perdre toutes ses vies.

---

## Compilation et exécution

### Prérequis

Pour compiler le projet et exécuter les tests, il est nécessaire d'installer la bibliothèque **Google Test**. Voici les instructions pour Linux et Windows :

- **Linux :** Consultez [ce guide](https://github.com/google/googletest/blob/main/googletest/README.md) pour installer les bibliothèques.
- **Windows :** Suivez les mêmes instructions adaptées à votre environnement.

### Instructions

#### Compilation

1. Placez-vous dans le répertoire du projet.
2. Pour compiler en mode texte :
   ```bash
   make
   ```
3. Pour compiler en mode SDL :
   ```bash
   make sdl
   ```
4. Pour exécuter les tests :
   - Placez-vous dans le répertoire des tests :
     ```bash
     cd tests
     ```
   - Ajoutez `../` devant tous les chemins des fichiers chargés (provisoire, ce point n'a pas encore été corrigé).
   - Compilez une classe spécifique en remplaçant `nom_classe` par le nom de la classe à tester :
     ```bash
     make nom_classe
     ```
   - Lancez le test :
     ```bash
     ./bin/nom_classe
     ```
     Exemple :
     ```bash
     make player
     ./bin/player
     ```

#### Exécution

- Pour lancer le jeu en mode texte :
  ```bash
  ./bin/jeu
  ```
- Pour lancer le jeu en mode SDL :
  ```bash
  ./bin/jeu_sdl
  ```

---

## Fonctionnalités techniques supplémentaires

- **Compatibilité multiplateforme :** Le jeu est conçu pour fonctionner sur les systèmes Windows et Linux sans ajustement majeur.
- **Optimisation :** Le moteur utilise des algorithmes simples pour garantir une exécution fluide à 60 FPS.
- **Modularité :** Le code est organisé de manière à faciliter l'ajout de nouveaux niveaux, ennemis ou power-ups dans les versions futures.

---

##

---

