# Philosophers - 42 School Project

![42 Badge](https://img.shields.io/badge/Score-125%2F100-success)
![Language](https://img.shields.io/badge/Language-C-blue)
![Threads](https://img.shields.io/badge/Threads-Pthread-orange)

## 📖 Description

Le projet **Philosophers** est une simulation du célèbre problème des philosophes dîneurs (Dining Philosophers Problem) créé par Edsger Dijkstra. Ce projet introduit les concepts fondamentaux de la programmation concurrente : threads, mutex, et synchronisation.

### Le Problème

- Des philosophes sont assis autour d'une table circulaire
- Ils alternent entre trois états : **manger**, **penser**, et **dormir**
- Il y a autant de fourchettes que de philosophes sur la table
- Un philosophe a besoin de **deux fourchettes** (gauche et droite) pour manger
- Les philosophes ne communiquent pas entre eux
- La simulation s'arrête si un philosophe meurt de faim

**L'objectif** : Empêcher qu'un philosophe meure tout en évitant les deadlocks et les data races.

## 🎯 Objectifs Pédagogiques

- Comprendre le fonctionnement des **threads** (pthread)
- Maîtriser les **mutex** pour la synchronisation
- Gérer les **ressources partagées** (fourchettes)
- Éviter les **deadlocks** et les **data races**
- Implémenter un système de **monitoring** en temps réel

## 🛠️ Compilation
```bash
make        # Compile le projet
make clean  # Supprime les fichiers objets
make fclean # Supprime les fichiers objets et l'exécutable
make re     # Recompile entièrement le projet
```

## 🚀 Utilisation
```bash
./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]
```

### Arguments

| Argument | Description |
|----------|-------------|
| `number_of_philosophers` | Nombre de philosophes (et de fourchettes) |
| `time_to_die` | Temps en ms avant qu'un philosophe meure sans manger |
| `time_to_eat` | Temps en ms qu'un philosophe prend pour manger |
| `time_to_sleep` | Temps en ms qu'un philosophe passe à dormir |
| `[must_eat_count]` | (Optionnel) Nombre de fois que chaque philosophe doit manger |

### Exemples
```bash
# Simulation simple avec 5 philosophes
./philo 5 800 200 200

# Simulation avec arrêt après 7 repas par philosophe
./philo 4 410 200 200 7

# Test de mort (un philosophe devrait mourir)
./philo 4 310 200 100

# Test avec un seul philosophe
./philo 1 800 200 200
```

## 📊 Format des Logs
```
timestamp_in_ms X has taken a fork
timestamp_in_ms X is eating
timestamp_in_ms X is sleeping
timestamp_in_ms X is thinking
timestamp_in_ms X died
```

**X** représente le numéro du philosophe (de 1 à number_of_philosophers)

## 🏗️ Structure du Projet
```
philosophers/
├── includes/
│   └── philosophers.h      # Headers et structures
├── srcs/
│   ├── philosophers.c      # Main : Point d'entrée
│   ├── parcing.c           # Parsing des arguments et validation
│   ├── init.c              # Initialisation des données et attribution des fourchettes
│   ├── dinner.c            # Routine principale (Manger, Dormir, Penser)
│   ├── monitor.c           # Thread observateur (vérifie la mort)
│   ├── getters_setters.c   # Accès thread-safe aux variables (Mutex)
│   ├── safe_fonctions.c    # Wrappers sécurisés (malloc, pthread_create...)
│   ├── write.c             # Affichage des logs protégé par mutex
│   ├── syncro_utils.c      # Outils de synchronisation (attente des threads)
│   └── utils.c             # Gestion du temps (gettimeofday) et nettoyage
└── Makefile
```

## 🧩 Concepts Clés

💡 Solutions Techniques
1. Gestion des Deadlocks (Interblocages)

Pour éviter que tous les philosophes prennent leur fourchette gauche en même temps et attendent indéfiniment la droite (ce qui bloquerait tout), j'ai implémenté une hiérarchie des ressources dans init.c :

    Les philosophes Impairs prennent d'abord la fourchette Gauche puis la Droite.

    Les philosophes Pairs prennent d'abord la fourchette Droite puis la Gauche. Cela brise le cycle d'attente circulaire.

2. Gestion des Data Races

Aucune variable partagée n'est lue ou écrite sans protection. J'utilise des fonctions "Wrappers" (dans getters_setters.c) qui verrouillent systématiquement un mutex avant de modifier ou lire une valeur sensible (comme last_meal_time ou simulation_finish).
3. Précision du Temps

usleep n'étant pas assez précis sur certains systèmes, j'ai codé une fonction precise_usleep (dans utils.c) qui combine usleep pour les longues attentes et une boucle active (spinlock) pour les dernières microsecondes, garantissant un timing parfait.

## ⚠️ Règles Importantes

- ❌ **Pas de variables globales**
- ✅ Pas de leaks mémoire
- ✅ Pas de data races
- ✅ Les messages de mort doivent s'afficher dans les **10ms** suivant la mort réelle
- ✅ Aucun philosophe ne doit mourir (sauf dans les cas de test)

## 🧪 Tests Recommandés
```bash
# Ne devrait pas mourir
./philo 5 800 200 200
./philo 4 410 200 200

# Devrait mourir
./philo 4 310 200 100

# Cas limite
./philo 1 800 200 200      # Un seul philosophe (doit mourir)
./philo 2 800 200 200      # Deux philosophes
./philo 200 800 200 200    # Beaucoup de philosophes
```

## 📚 Ressources Utiles

- [Pthread Documentation](https://man7.org/linux/man-pages/man7/pthreads.7.html)
- [Dining Philosophers Problem](https://en.wikipedia.org/wiki/Dining_philosophers_problem)
- [Thread Synchronization](https://www.geeksforgeeks.org/mutex-lock-for-linux-thread-synchronization/)

## 👨‍💻 Auteur

**Asmati** - Étudiant 42 School

---

*"I never thought philosophy would be so deadly"* 🍝
