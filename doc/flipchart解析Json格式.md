# flipchart解析Json格式


##  flipchart对象字段说明
现在已解析的对象如下:

*Object*

* [Annotation](#Annotation)
* [Background](#Background)
* [Color](#Color)
* [Grid](#Grid)
* [Image](#Image)
* [Ink](#Ink)
* [MediaContainer](#MediaContainer)
* [Page](#Page)
* [Point](#Point)
* [RenderableGroup](#RenderableGroup)
* [Shape](#Shape)
* [ShapeElement](#ShapeElement)
* [Size](#Size)
* [Text](#Text)
* [TextRun](#TextRun)
* [Transform](#Transform)
* [Connector](#Connector)



*Enum*

* [EnumInkType](#EnumInkType)
* [EnumBrushStyle](#EnumBrushStyle)
* [EnumPenJoinStyle](#EnumPenJoinStyle)
* [EnumPenCapStyle](#EnumPenCapStyle)
* [EnumPenStyle](#EnumPenStyle)
* [EnumTileFit](#EnumTileFit)
* [EnumBrushGradientType](#EnumBrushGradientType)


### <a name="Page"></a> Page
* id 对象id （int）
* objects 页内对象集合数组
- `-` property

    propertyKey |Type| Description
    ------------|----|------------
    gridVisible |  bool |栅格是否可见
    name |string| 页对象名称
    overlayBackground| bool |未知
    pageFrameSize|size| 页边框大小
    pageSize|size|页面大小
    perPageTransition||
    revealedDistance||
    revealerMode||
    originPoint|vector2|页面坐标原点

* softParentIds group的父节点id集合 (`Array<int>`)
* type 对象类型名 （string）

### <a name="Background"></a>Background
* id 对象id （int）
- `-`property

	propertyKey |Type| Description
	------------|----|------------
	backgroundInk|Ink|墨迹属性
	backgroundImage|Image|背景图像对象

* backgoundType(int)背景类型 0:色彩背景 1:图片背景
* type 类型名 （string）

### <a name="Ink"></a> Ink
* 属性信息
    propertyKey |Type| Description
    ------------|----|------------
    inkType|[EnumInkType](#EnumInkType)|画笔类型 只适用于annotation元素
	strokePenCapStyle|[EnumPenCapStyle](#EnumPenCapStyle)|绘制路径端点样式
	strokePenColor|[Color](#Color)|绘制路径颜色
	strokeJoinStyle|[EnumPenJoinStyle](#EnumPenJoinStyle)|绘制路径转角样式
	strokeStyle|[EnumPenStyle](#EnumPenStyle)|绘制路径样式
	strokePenWidth|int|绘制路径宽度
    backgroudMode|int|背景模式 0透明背景 1不透明背景
    backgroundColor|[Color](#Color)|背景色 当backgroundMode 为1时有效
    brushColor|[Color](#Color)|画笔颜色 普通画笔样式使用的颜色
	brushColor2|[Color](#Color)|画笔2颜色 梯度画笔样式使用的第二种颜色
	brushGradientType|[EnumBrushGradientType](#EnumBrushGradientType)| 画笔色彩梯度类型
	brushStyle|[EnumBrushStyle](#EnumBrushStyle)| 画笔风格



### <a name="Grid"></a>Grid
* id 对象id （int）
- `-` property

	propertyKey |Type| Description
	------------|----|------------
	allowSnap |bool|
	thumbNailScale |double|缩略图缩放比例？
	brushGradientType|int| 画笔色彩梯度类型
	boundingRect |rect| 对象包围盒
	defaultScale |double|默认缩放比例
	keywords |stringList|关键词数组
	layer|int|图层id
	levelEditor |bool|
    rotateOrigin |vector2|旋转中心坐标
	scaleOrigin |vector2|缩放中心坐标
	scaleStep |double|缩放步距
	twips|vector2|
	visible|bool|是否可见
	zOrder|int|渲染顺序？

* ink 墨迹属性 (Ink)
* softParentIds group的父节点id集合 (`Array<int>`)
* transform 对象几何变换属性 （Transform）
* type 类型名 （string）

### <a name="Transform"></a>Transform
* id 对象id （int）
* angle(double) 旋转角度
* inverted (bool)是否反转
* reflected (bool)是否反射？
* scaleFactor (Pointx) y 缩放比列
* translate (Point) 对象相对于bounding rect top（对应y） left（对应x） x y 轴需要偏移的距离

* type 类型名 （string）

### <a name="Point"></a>Point
* x 坐标 （double）
* y 坐标  (double）

### <a name="Annotation"></a>Annotation
* id 对象id （int）
- `-` property

	propertyKey |Type| Description
	------------|----|------------
	boundingRect |rect| 对象包围盒
	endCapA |int| 结束点样式
	endCapB |int| 结束点样式
	layer |int| 图层id
	name|int|对象名称
	resource|int|资源id
    rotateOrigin |vector2|旋转中心坐标
	scaleOrigin |vector2|缩放中心坐标
    translucency|int| 透明度
	zOrder|int|渲染次序

* ink 墨迹属性 (Ink)
* softParentIds group的父节点id集合 (`Array<int>`)
* type 类型名 （string）
- `-` resource   （annotation点集资源数组）  （pointArray）

    resourceKey |Type| Description
    ------------|----|------------
    pointArray|Vector2 Array| 点集数组 存储point对象

* transform 对象几何变换属性 （Transform）

### <a name="Image"></a>Image
* id 对象id （int）
- `-` property

	propertyKey |Type| Description
	------------|----|------------
	boundingRect |Rect| 对象包围盒
	layer |int| 图层id
	name|int|对象名称
	resource|int|资源id
	rotateOrigin |vector2|旋转中心坐标
	scaleOrigin |vector2|缩放中心坐标
	tileFit|[EnumTileFit](#EnumTileFit)|图片平铺方式
	tiled|bool|是否平铺显示图片
	tileArea|size|平铺显示时的区域
	transparent |bool| 对象是否透明
	transparentColor|color| 透明度颜色
	zOrder|int|渲染次序

* softParentIds group的父节点id集合 (`Array<int>`)
* type 类型名 （string）
- `-` resource   （image图片资源路径）

    resourceKey |Type| Description
    ------------|----|------------
    imageUrl |string| image对象的图片路径

* transform 对象几何变换属性 （Transform）


### <a name="Text"></a>Text
* id 对象id （int）
- `-` property

	propertyKey |Type| Description
	------------|----|------------
	boundingRect |Rect| 对象包围盒
	layer |int| 图层id
	name|int|对象名称
	resource|int|资源id
	rotateOrigin |vector2|旋转中心坐标
	scaleOrigin |vector2|缩放中心坐标
	zOrder|int|渲染次序

* ink 墨迹属性 (Ink)
* softParentIds group的父节点id集合 (`Array<int>`)
* type 类型名 （string）
- `-` resource   （text多行文本资源）

    resourceKey |Type| Description
    ------------|----|------------
    textRunArray |Array| 存储每一行本文的 TextRun对象

* transform 对象几何变换属性 （Transform）


### <a name="TextRun"></a>TextRun
* boundingRect 文字包围盒 (Rect)
* bulletPosition 子弹文字位置 (vector2)
* bulletText 子弹文字？？ (string)
* fontFamily 字体 （string）
* fontSize 字体大小 （double）
* position 文字相对于Text对象的坐标 （vector2）
* text 文字内容 （string）
* textColor 文字颜色 （Color）

### <a name="RenderableGroup"></a>RenderableGroup
* id 对象id （int）
- `-` property

	propertyKey |Type| Description
	------------|----|------------
	boundingRect |Rect| 对象包围盒
	layer |int| 图层id
	name|int|对象名称
	rotateOrigin |vector2|旋转中心坐标
	scaleOrigin |vector2|缩放中心坐标
    v2Group|bool|是否是V2版本flipchart group
    zOrder|int|渲染次序

* ink 墨迹属性 (Ink)
* softChildIds  group的子节点id集合 (`Array<int>`)
* softParentIds group的父节点id集合 (`Array<int>`)
* transform 对象几何变换属性 （Transform）
* type 类型名 （string）

### <a name="Shape"></a>Shape
* id 对象id （int）
- `-` property

	propertyKey |Type| Description
	------------|----|------------
	boundingRect |Rect| 对象包围盒
    endAIndex|int|
    endAPos|vector2|
    endAShapeCenterDiff|vector2|
    endBIndex|int|
    endbPos|vector2|
    endBShapeCenterDiff|vector2|
    endCapA|int|
    endCapB|int|
    fillMode|int| 暂时没有发现绘制时使用
    innerDiam|double|
    intelligent|bool|
    isConnector|bool|
    isOpen|bool|shape是否闭合   不闭合时不填充形状
    isStar|bool|是否是星形
	layer |int| 图层id
    localPoints|vector2|
	name|int|对象名称
    numShapePoints|int|
    resource|int|shape的资源id号
	rotateOrigin |vector2|旋转中心坐标
	scaleOrigin |vector2|缩放中心坐标
    shapeType|int|当前shape的类型   当值为 1, 2 , 3 时resource中直接存储点集 当值为 4 ,5 时存储多类型元素集合
    v2Type|int|V2版本flipchart 类型
    zOrder|int|渲染次序

- `-` resource   （shape的元素集合）

    当shapeType值为 0,1,2 ,3
    resourceKey |Type| Description
    ------------|----|------------
    pointArrayArray |`Array<Array<vector2>>`| 存储点集的集合

    当shapeType值为 4 ,5
    resourceKey |Type| Description
    ------------|----|------------
    shapeElements |`Array<Array<ShapeElement>>`| 存储点集的集合

* ink 墨迹属性 (Ink) 填充时使用 brushcolor  brushstyle 为0 时也不填充     边框使用 penColor  penwidth等数据
* softParentIds group的父节点id集合 (`Array<int>`)
* transform 对象几何变换属性 （Transform）
* type 类型名 （string）

###<a name="ShapeElement"></a>ShapeElement

- `-` 椭圆独有属性
* majorAxisRadius 椭圆长轴半径 (double)
* minorAxisRadius 椭圆短轴半径  (double)
* clockWise  椭圆是否是顺时针绘制(bool)
* largeArc  ?


- `-` 椭圆,直线,下笔点 共有属性
* endpoint 结束点(vector2)
* type 类型名(string) 椭圆为ellipse 直线为line 下笔点为movement;


###<a name="MediaContainer"></a>MediaContainer
* id 对象id （int）
- `-` property

	propertyKey |Type| Description
	------------|----|------------
    autoPlay|bool|是否自动播放
	boundingRect |Rect| 对象包围盒
	layer |int| 图层id
	name|int|对象名称
    numShapePoints|int|
    placeHolderResource|int|封面截图资源id号
    resource|int|shape的资源id号
	rotateOrigin |vector2|旋转中心坐标
	scaleOrigin |vector2|缩放中心坐标
    transparentBackground|bool|是否背景透明
    zOrder|int|渲染次序

- `-` resource   （shape的元素集合）

     * mediaUrl  (string)视频文件路径
     * tumbFileUrl(string)封面图片文件路径

* softParentIds group的父节点id集合 (`Array<int>`)
* transform 对象几何变换属性 （Transform）
* type 类型名 （string）

###<a name="Connector"></a>Connector
* id 对象id （int）
- `-` property

	propertyKey |Type| Description
	------------|----|------------
	boundingRect |Rect| 对象包围盒
    endAIndex|int|起始对象上连接的点的次序
    endAPos|vector2|起始点坐标
    endAShapeCenterDiff|vector2|
    endBIndex|int|结束对象上连接的点的次序
    endbPos|vector2|终止点坐标
    endBShapeCenterDiff|vector2|
    endCapA|int|
    endCapB|int|
    fillMode|int| 暂时没有发现绘制时使用
    innerDiam|double|
    intelligent|bool|
    isConnector|bool|
    isOpen|bool|shape是否闭合   不闭合时不填充形状
    isStar|bool|是否是星形
	layer |int| 图层id
    localPoints|vector2|
	name|int|对象名称
    numShapePoints|int|
    resource|int|shape的资源id号
	rotateOrigin |vector2|旋转中心坐标
	scaleOrigin |vector2|缩放中心坐标
    shapeType|int|connector对象此属性无效
    v2Type|int|V2版本flipchart 类型
    zOrder|int|渲染次序

* ink 墨迹属性 (Ink) 填充时使用 brushcolor  brushstyle 为0 时也不填充     边框使用 penColor  penwidth等数据
* softParentIds group的父节点id集合 (`Array<int>`)
* transform 对象几何变换属性 （Transform）
* type 类型名 （string）


### <a name="Color"></a>Color
* a Alpha通道值标定透明度 （int）
* r Red  (int)
* g Green  (int)
* b Blue  (int)

### <a name="Rect"></a>Rect
* height  (double)
* left    (double)
* top     (double)
* width   (double)

### <a name="Size"></a>Size
* width   (double)
* height  (double)

### <a name="EnumTileFit"></a> EnumTileFit

    {
        AS_TILEFIT_NONE = 0, //不适配
        AS_TILEFIT_BESTFIT,//最佳适配
        AS_TILEFIT_STRETCHFIT,//拉伸时配
        AS_TILEFIT_CENTRE,//居中
        AS_TILEFIT_TOPLEFT,//左上角
        AS_TILEFIT_TOPCENTRE,//顶部中心
        AS_TILEFIT_TOPRIGHT,//右上角
        AS_TILEFIT_LEFTCENTRE,//左侧中心
        AS_TILEFIT_RIGHTCENTRE,//右侧中心
        AS_TILEFIT_BOTTOMLEFT,//左下角
        AS_TILEFIT_BOTTOMCENTRE,//底部中心
        AS_TILEFIT_BOTTOMRIGHT//右下角
};

### <a name="EnumPenStyle"></a>EnumPenStyle
    enum AsEnumPenStyle
    {
        AS_PENSTYLE_NONE = 0,
        AS_PENSTYLE_SOLIDLINE,//实线___________________
        AS_PENSTYLE_DASHEDLINE,//虚线--------
        AS_PENSTYLE_DOTLINE,//点画虚线  ........
        AS_PENSTYLE_DASHDOTLINE,//线点虚线-.-.-.
        AS_PENSTYLE_DASHDOTDOTLINE//一线双点虚线-..-..-
    };

###<a name="EnumPenCapStyle"></a>EnumPenCapStyle
     enum AsEnumPenCapStyle
    {
        AS_PENCAPSTYLE_FLAT = 0x0, //端点不处理
        AS_PENCAPSTYLE_SQUARE = 0x10,//矩形端点
        AS_PENCAPSTYLE_ROUND = 0x20//圆形端点
    };

###<a name="EnumInkType"></a>EnumInkType
    enum AsEnumInkType
    {
        AS_INKTYPE_NORMAL = 0,//一般笔迹
        AS_INKTYPE_HIGHLIGHT,//荧光笔
        AS_INKTYPE_MASK//魔法墨水笔迹
    };

###<a name="EnumPenJoinStyle"></a>EnumPenJoinStyle
    enum EnumPenJoinStyle
    {
        AS_PENJOINSTYLE_MITER = 0,//端点直接连接
        AS_PENJOINSTYLE_BEVEL = 0x40,//端点斜线衔接
        AS_PENJOINSTYLE_ROUND = 0x80//端点圆弧衔接
    };

###<a name="EnumBrushStyle"></a>EnumBrushStyle
    enum EnumBrushStyle
    {
        AS_BRUSHSTYLE_NONE = 0,//无画刷
        AS_BRUSHSTYLE_SOLID,//实心
        AS_BRUSHSTYLE_DENSE1,//密度1
        AS_BRUSHSTYLE_DENSE2,
        AS_BRUSHSTYLE_DENSE3,
        AS_BRUSHSTYLE_DENSE4,
        AS_BRUSHSTYLE_DENSE5,
        AS_BRUSHSTYLE_DENSE6,
        AS_BRUSHSTYLE_DENSE7,
        AS_BRUSHSTYLE_HORIZONTAL,//水平
        AS_BRUSHSTYLE_VERTICAL,//垂直
        AS_BRUSHSTYLE_CROSS,//交叉
        AS_BRUSHSTYLE_BACKWARDDIAGONAL,//对角线后退
        AS_BRUSHSTYLE_FOWARDDIAGONAL,//对角线前进
        AS_BRUSHSTYLE_CROSSDIAGONAL,//对角线交叉
        AS_BRUSHSTYLE_TEXTURE = 24,//图片填充
        AS_BRUSHSTYLE_GRADIENT = 25//梯度填充
    };

###<a name="EnumBrushGradientType"></a>EnumBrushGradientType
     enum AsEnumBrushGradientType
    {
        AS_BRUSHGRADIENT_NONE		= 0,//无梯度
        AS_BRUSHGRADIENT_VERTICAL	= 1,//垂直
        AS_BRUSHGRADIENT_HORIZONTAL = 2,//水平
        AS_BRUSHGRADIENT_DIAGONAL1	= 3,//正对角线   \
        AS_BRUSHGRADIENT_DIAGONAL2	= 4,//逆对角线    /
        AS_BRUSHGRADIENT_RADIAL		= 5 //射线
    };