/*==========================================================================;
 *
 *  ������Ϸ���棨Light Game Engine��
 *
 *  ��Ȩ���� (C) 2005-2009 �� �� ��������Ȩ����
 *  Copyright (C) KangXu.  All Rights Reserved.
 *
 *  �˽�������������� http://www.lightengine.cn
 *
 *  �ļ�:   light.h
 *  ����:   ������Ϸ����ͷ�ļ�
 *
 ****************************************************************************/


//////////////////////////////////////////////////////////////////////////////
//                                                                          //
//                                                                          //
//  ��������( Light Engine )��һ��ǳ������������� 3D ��Ϸ���档���ڸ���  //
//  ������������Ϸ��������ʵϵͳ�Ŀ�������һ��ͨ�õ� 3D ��Ϸ���棬3D ͼ�ν� //
//  �ڲ��� OpenGL ����Ϸ���������� C++�����ý�ͬʱ֧�� VB ��������й���ǿ  //
//  �󡢻��ʱ��桢���ٸ�Ч���������Ĵ��ص㣬��Ϊ�ɹ���Ǹ�������ȫ���    //
//  ���������˺���ҵ��;��������������Ϸ������ѡ��                        //
//                                                                          //
//                                                                          //
//  �������������ϵ��                                                      //
//                                                                          //
//  ��������ȱʡ������ OpenGL ��ͬ������ϵ���� x ��ָ���ң� y ��ָ���ϣ�    //
//  z ��ָ����Ļ���档����ͼ��ʾ��                                          //
//                                                                          //
//                    ��y                                                   //
//					  �O                                                    //
//					  �O   x                                                //
//					 �u-----��                                              //
//                 �Lz                                                      //
//			                                                                //
//                                                                          //
//  ��������ͬʱҲ֧�� 3DSMAX ������ϵ���� x ��ָ���ң� z ��ָ���ϣ�        //
//  y ��ָ����Ļ���档����ͼ��ʾ��                                          //
//                                                                          //
//                    ��z                                                   //
//					  �O  �Jy                                               //
//					  �O�u   x                                              //
//					   -----��                                              //
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