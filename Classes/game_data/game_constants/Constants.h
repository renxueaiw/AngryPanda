//
//  Constants.h
//  AngryPanda
//
//  Created by renxueaiw on 13-11-30.
//
//

#ifndef AngryPanda_Constants_h
#define AngryPanda_Constants_h

// 判断设置类型
//#define kDeviceTypeNotIphone5 0
//#define kDeviceTypeIphont5OrNewTouch 1
#define kDeviceAndroid

//#define IS_IPHONE (!IS_IPAD)
//#define IS_IS_IPAD (UI_USER_INTERFACE_IDIOM != UIUserInterfaceIdiomPhone)
//#define IS_ANDROID IS_ANDROID

// Box2D世界与Cocos2D世界坐标切换
#define PTM_RATIO 32

// 精灵对象在层中的z-order(显示层级)值
#define zOrderClouds    -300   // 云
#define zOrderParticles -299    // 粒子系统
#define zOrderHills     -298    //  小山
#define zOrderFloor     -290    // 地板
#define zOrderScore     -285    // 得分

#define zOrderWhiteDots -205    // 白点

#define zOrderStrapBack -202    // 皮带后
#define zOrderPlatform  -201    // 站台
#define zOrderPandas    -200    // 熊猫
#define zOrderStack     -199    // 堆叠(障碍物)

#define zOrderSlingShotFront -179   // 投石机发射前面
#define zOrderStrapFront    -178    // 皮带前面

#define zOrderVisualEffect  50  // 虚拟效果
#define zOrderPointScore    100 // 得分点

#define zOrderChapterBg -100 // 章节背景
#define zOrderLevelBg   -100 // 关卡背景
#define zOrderLevelText 10 // 关卡文本

// 标识
#define tagForWhiteDotsEvenNumberedTurn 1000
#define tagForWhiteDotsOddNumberedTurn 2000

// 物体形状的创建方法
#define useShapeOfSourceImage 0 // (源图形状)用于方形和矩形
#define useTriangle 1 // (三角)图片左下角，右下角和中心点的顶点值
#define useTrapezoid 3 // (梯形)图片左下角、右下角，顶部1/4和3/4处的顶点值（
#define useDiameterOfImageForCicle 4 // (圆图的直径)用于完美的图形
#define customeCoordinates 100 // 使用类似Vertex Helper Pro等工具获取定点坐标在定义定制的顶点坐标时，必须按逆时针顺序进行，且最多只能只能有8个顶点，且必须形成凸面。）

#define breakEffectNone 0   // 中断效果
#define breakEffectSmokePuffs 1 // 中断效果烟雾喷射
#define breakEffectExplosion 2 // 中断效果爆炸 

#endif
