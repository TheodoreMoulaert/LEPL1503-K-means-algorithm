
#ifndef CLUSTER_H
#define CLUSTER_H

/*
Structure qui  permet de définir les clusters et les centroïds tel que 
cluster est défini par cluster_t** et centroids est défini par cluster_t* 
*/ 
typedef struct {
    point_t center;
    uint64_t surrounding;
    point_t *data;

} cluster_t;

#endif //CLUSTER_H
