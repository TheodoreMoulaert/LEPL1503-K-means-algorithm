#ifndef PORTABLE_SEMAPHORE_H
#define PORTABLE_SEMAPHORE_H

#include <semaphore.h>
#include <stdint.h>
#include <stdlib.h>

/**
 * Initialise un sémaphore avec la valeur spécifiée.
 * Sur macOS, utilise sem_open avec un nom temporaire.
 * Sur les autres plateformes, utilise sem_init.
 *
 * @param value La valeur initiale du sémaphore.
 * @return Un pointeur vers le sémaphore initialisé, ou NULL en cas d'échec.
 */
static inline sem_t *
my_sem_init(uint32_t value)
{
#ifdef __APPLE__
    char *name = "/tmp/myPortableSem";
    sem_unlink(name);
    return sem_open(name, O_CREAT, 0644, value);   
#else
    sem_t *sem = (sem_t *)malloc(sizeof(sem_t));
    if (!sem)
    {
        return NULL;
    }
    if (sem_init(sem, 0, value) != 0)
    {
        free(sem);
        return NULL;
    }
    return sem;
#endif /* __APPLE__ */
}

/**
 * Détruit le sémaphore spécifié et libère la mémoire associée.
 * Sur macOS, utilise sem_close.
 * Sur les autres plateformes, utilise sem_destroy et libère la mémoire manuellement.
 *
 * @param sem Le pointeur vers le sémaphore à détruire.
 * @return 0 en cas de succès, -1 en cas d'erreur.
 */

static inline int
my_sem_destroy(sem_t *sem)
{
#ifdef __APPLE__
    return sem_close(sem);
#else
    int err = sem_destroy(sem);
    free(sem);
    return err;
#endif /* __APPLE__ */
}

// Define to hide the portable semaphore
#define sem_init(value) my_sem_init(value)
#define sem_destroy(sem) my_sem_destroy(sem)
// sem_wait and sem_post are equivalent for OSX and Linux => use default function calls

#endif /* PORTABLE_SEMAPHORE_H */
