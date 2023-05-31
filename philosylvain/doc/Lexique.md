## Thread
Un thread (ou fil d'exécution en français) est une unité d'exécution légère au sein d'un processus. Un processus peut contenir plusieurs threads, chacun exécutant une tâche différente simultanément.

Chaque thread a son propre point d'exécution et peut être planifié indépendamment par le système d'exploitation pour s'exécuter sur un ou plusieurs processeurs disponibles. Les threads partagent les ressources du processus, comme la mémoire, les fichiers ouverts, les signaux et les descripteurs de fichiers.

Les threads sont souvent utilisés pour paralléliser des tâches dans lesquelles une partie du travail peut être exécutée de manière indépendante, permettant ainsi de gagner du temps et d'optimiser l'utilisation des ressources. Les threads sont également utilisés pour améliorer la réactivité des applications en permettant à des tâches lourdes de s'exécuter en arrière-plan tout en laissant l'interface utilisateur réactive.

---
## Mutex
Un mutex (contraction de mutual exclusion, ou exclusion mutuelle en français) est un objet de synchronisation utilisé pour éviter que plusieurs threads accèdent simultanément à une ressource partagée, telle que la mémoire, et entraînent des problèmes de concurrence ou de cohérence de données.

Un mutex est associé à une section critique de code, c'est-à-dire une partie de code qui doit être exécutée de manière atomique, c'est-à-dire sans être interrompue par un autre thread. Lorsqu'un thread souhaite entrer dans la section critique, il tente de verrouiller le mutex. Si le mutex est déjà verrouillé par un autre thread, le thread est mis en attente jusqu'à ce que le mutex soit déverrouillé par le thread qui le détient.

Une fois qu'un thread a verrouillé le mutex, il peut exécuter la section critique en toute sécurité, sachant qu'aucun autre thread ne peut y accéder simultanément. Une fois que la section critique est terminée, le thread doit déverrouiller le mutex, permettant ainsi à un autre thread d'y accéder.

---
## pthread_create
La fonction pthread_create() est utilisée pour créer un nouveau thread. Elle prend quatre arguments : un pointeur vers une variable pthread_t qui identifiera le thread créé, un pointeur vers une structure pthread_attr_t qui contient les attributs du thread (par défaut NULL), un pointeur vers la fonction que le thread doit exécuter, et un pointeur vers les arguments de la fonction.

---
## pthread_join
La fonction pthread_join() est utilisée pour attendre qu'un thread se termine et récupérer sa valeur de retour. Elle prend deux arguments : le pthread_t du thread à rejoindre et un pointeur vers un emplacement qui contiendra la valeur de retour du thread.