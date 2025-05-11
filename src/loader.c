#include "loader.h"

MAP loadMap(char* path){
  MAP map = {NULL,NULL,-1};
  FILE* fp = fopen(path,"r");
  if (fp){
    fscanf(fp,"%d",&map.nSectors); //Read how many sector does this map contains
    map.sectors = (SECTOR*)malloc(map.nSectors*sizeof(SECTOR)); //Allocate memory for the sectors
    map.visitedSectors = (int*)malloc(map.nSectors*sizeof(int)); //Allocate memory for the sectors
    for(int s = 0; s < map.nSectors; s+=1){
      //Read current sector info
      fscanf(fp,"%d %d %d %d",&map.sectors[s].id,&map.sectors[s].nWalls, &map.sectors[s].zfloor,&map.sectors[s].zceiling);
      printf("[ SECTOR %d ]\n",map.sectors[s].id);
      printf("zFloor %d zCeiling %d\n",map.sectors[s].zfloor,map.sectors[s].zceiling);
      map.sectors[s].walls = (WALL*)malloc(map.sectors[s].nWalls*sizeof(WALL));
      WALL* walls = map.sectors[s].walls;
      for (int w = 0; w < map.sectors[s].nWalls; w+=1){
        fscanf(fp,"%f %f %f %f %d",&walls[w].p1.x,&walls[w].p1.y,&walls[w].p2.x,&walls[w].p2.y,&walls[w].neighborSector);
        printf("p1 %.2f %.2f ",walls[w].p1.x,walls[w].p1.y);
        printf("p2 %.2f %.2f\n",walls[w].p2.x,walls[w].p2.y);
      }
      printf("\n");
    }
    fclose(fp);
    printf("MAP LOADED SUCCESFULLY\n");
  }
  return map;
}

void freeMap(MAP* map){
  for(int i = 0; i < map->nSectors; i++){
    free(map->sectors[i].walls); map->sectors[i].walls = NULL;
  }
  free(map->sectors); map->sectors = NULL;
}
