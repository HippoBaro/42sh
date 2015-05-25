# L'essentiel du projet
    * Un 42sh fonctionnel.

# Les bonus implémentés
    * Un man (ShugarSh.1)
    * Interface TERMCAPS
    * Edition complète de la ligne de commande (GAUCHE, DROITE, SUPPR, DEL)
    * alias et unalias (~/.ShugarShrc)
    * history (avec la gestion du '!') (~/.ShugarShrc.history)
    * "import" recharge les alias et l'historique manuellement depuis
      leur fichier respectif.
    * Autocomplétion avec TAB
    * Gestion des variables (ex. "echo $USER")
    * Backgrounding avec l'opérateur unaire '&'
    * Gestion du glob (seulement pour l'oéprateur '*'). Pas de RegEx.
    * Tapez "StillAlive" pour un super bonus de la mort qui tue. (Seulement
      avec le binaire compilé via le Makefile incluant la SDL).
    * Tapez "StarWars" pour un bonus qui vaux (au moins) 42! points.

# Raccourcis clavier
    * CTRL+L   : Clear le terminal
    * CTRL+R   : Affiche l'historique (= "history")
    * TAB      : Autocomplétion
    * HAUT/BAS : Navigation dans l'historique

With love,
barrau_h.
