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
│   └── philo.h           # Header principal
├── srcs/
│   ├── philo.c           # Point d'entrée du programme
│   ├── parsing.c         # Validation et parsing des arguments
│   ├── init.c            # Initialisation des structures
│   ├── thread.c          # Création et gestion des threads
│   ├── routine.c         # Routine principale des philosophes
│   ├── actions.c         # Actions des philosophes (eat, sleep, think)
│   ├── monitor.c         # Surveillance des philosophes
│   └── utils/
│       ├── utils.c       # Fonctions utilitaires
│       └── cleanup.c     # Nettoyage et libération mémoire
└── Makefile
```

## 🧩 Concepts Clés

### Threads
Chaque philosophe est représenté par un **thread** indépendant qui exécute sa propre routine (penser, manger, dormir) en parallèle.

### Mutex
Les **mutex** (mutual exclusion) sont utilisés pour :
- Protéger chaque fourchette (éviter qu'elle soit prise par deux philosophes)
- Protéger l'affichage (éviter les messages entrelacés)
- Protéger les variables partagées (état de mort, compteur de repas)

### Éviter les Deadlocks
Un **deadlock** survient quand tous les philosophes prennent leur fourchette gauche en même temps et attendent leur fourchette droite. Solutions implémentées :
- Les philosophes pairs attendent un peu avant de commencer
- Attribution stratégique des fourchettes (gauche/droite)

### Data Races
Les **data races** sont évités en protégeant toutes les variables partagées avec des mutex appropriés.

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

**tbhuiyan** - Étudiant 42 School

---

*"I never thought philosophy would be so deadly"* 🍝
