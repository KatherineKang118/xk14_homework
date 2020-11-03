//
//  triangle.hpp
//  xk14 Xiaoyin Kang
//
//  Created by 颜昕 on 11/1/20.
//

#ifndef triangle_hpp
#define triangle_hpp

#include <stdio.h>

#endif /* triangle_hpp */

#include "Ball.h"
#include "ofMain.h"

class triangleBall : public Ball {  // TrangleBall class **inherits** from Ball class
    
public:
    
    triangleBall();
    
    void draw(); // this will **override** the draw function inherited from Ball
    
};
