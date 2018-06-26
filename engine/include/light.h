/*==========================================================================;
 *
 *  光线游戏引擎（Light Game Engine）
 *
 *  版权所有 (C) 2005-2009 康 旭。 保留所有权利。
 *  Copyright (C) KangXu.  All Rights Reserved.
 *
 *  了解更多情况，请访问 http://www.lightengine.cn
 *
 *  文件:   light.h
 *  内容:   光线游戏引擎头文件
 *
 ****************************************************************************/


//////////////////////////////////////////////////////////////////////////////
//                                                                          //
//                                                                          //
//  光线引擎( Light Engine )是一款非常优秀的著名免费 3D 游戏引擎。用于各种  //
//  单机、网络游戏和虚拟现实系统的开发，是一款通用的 3D 游戏引擎，3D 图形接 //
//  口采用 OpenGL ，游戏开发语言是 C++，不久将同时支持 VB 。引擎具有功能强  //
//  大、画质逼真、快速高效、简单易用四大特点，更为可贵的是该引擎完全免费    //
//  （包括个人和商业用途），是您开发游戏的明智选择。                        //
//                                                                          //
//                                                                          //
//  光线引擎的坐标系：                                                      //
//                                                                          //
//  光线引擎缺省采用与 OpenGL 相同的坐标系，即 x 轴指向右， y 轴指向上，    //
//  z 轴指向屏幕外面。如下图所示：                                          //
//                                                                          //
//                    ↑y                                                   //
//					  ∣                                                    //
//					  ∣   x                                                //
//					 ╱-----→                                              //
//                 ↙z                                                      //
//			                                                                //
//                                                                          //
//  光线引擎同时也支持 3DSMAX 的坐标系，即 x 轴指向右， z 轴指向上，        //
//  y 轴指向屏幕里面。如下图所示：                                          //
//                                                                          //
//                    ↑z                                                   //
//					  ∣  ↗y                                               //
//					  ∣╱   x                                              //
//					   -----→                                              //
//                                                                          //
//			                                                                //
//                                                                          //
//////////////////////////////////////////////////////////////////////////////


#ifndef _LIGHT_ENGINE_H
#define _LIGHT_ENGINE_H

extern "C"
{

#include "config.h"
#include "type.h"
#include "3dmath.h"
#include "texture.h"
#include "sky.h"
#include "actor.h"
#include "md3.h"
#include "bsp.h"
#include "sound.h"
#include "input.h"
#include "image.h"
#include "text.h"
#include "video.h"
#include "camera.h"
#include "brush.h"
#include "lensflare.h"
#include "frustum.h"
#include "lighting.h"
#include "billboard.h"
#include "skeleton.h"
#include "particle.h"

#ifdef LIGHT_CORPORATION_EDITION

#include "joint.h"
#include "shader.h"
#include "terrain.h"
#include "water.h"
#include "weather.h"
#include "browser.h"
#include "fluidEmitter.h"
#include "fluid.h"

#endif

#include "mesh.h"
#include "animation.h"
#include "script.h"
#include "level.h"
#include "log.h"
#include "character.h"
#include "physicsMaterial.h"
#include "scene.h"
#include "fog.h"
#include "engine.h"
#include "startup.h"

}

#endif