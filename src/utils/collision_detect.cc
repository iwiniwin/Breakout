#include "collision_detect.h"

bool CollisionDetect::CheckAABB(glm::vec4 rect1, glm::vec4 rect2){
    if(rect1.z > rect2.x && rect2.z > rect1.x && rect1.w > rect2.y && rect2.w > rect1.y)
        return true;
    return false; 
}