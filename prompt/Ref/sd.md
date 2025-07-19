# 提示词生成图片

[TOC]

<div style="page-break-after: always;"></div>

## 通用

* 正向提示词
  
  正向提示词构成逻辑为：**通用的lora模型+触发词+内容描述词+通用描述画面质量词**
  
  正向提示词由:「内容」+「风格」两部分组成
  
  * 内容(略)
  
  * 风格
  
    * style of Andreas Achenbach,painting,oil,landscape 适合风景
  
    ![image](https://help-static-aliyun-doc.aliyuncs.com/assets/img/zh-CN/2893894271/p842376.png)
  
    - style of Claude Monet,oil painting
  
      ![image](https://help-static-aliyun-doc.aliyuncs.com/assets/img/zh-CN/2893894271/p842379.png)
  
    - style of Vinvent Van gogh,oil painting
  
      ![image](https://help-static-aliyun-doc.aliyuncs.com/assets/img/zh-CN/2893894271/p842380.png)
  
    - style of Norman Ackroyd,aquatint,landscape,B&W 适合风景
  
      ![image](https://help-static-aliyun-doc.aliyuncs.com/assets/img/zh-CN/2893894271/p842384.png)
  
    - style of Mike Allred,DC,comic 适合人像
  
      ![image](https://help-static-aliyun-doc.aliyuncs.com/assets/img/zh-CN/2893894271/p842386.png)
  
    - style of Edwin Austin Abbey,illustration, painting,oil,pastel,ink,USA 适合场景
  
      ![image](https://help-static-aliyun-doc.aliyuncs.com/assets/img/zh-CN/2893894271/p842388.png)
  
    - style of Albrecht Altdorfer,painting,oil,engraving,germany, 16th century 适合风景
  
      ![image](https://help-static-aliyun-doc.aliyuncs.com/assets/img/zh-CN/2893894271/p842390.png)
  
    - style of Alois Arnegger, painting,oil,landscape,portrait,expressionism 适合风景
  
      ![image](https://help-static-aliyun-doc.aliyuncs.com/assets/img/zh-CN/2893894271/p842392.png)
  
    - style of Cuno Amiet,painting,oil,landscape,expressionism 适合风景
  
      ![image](https://help-static-aliyun-doc.aliyuncs.com/assets/img/zh-CN/2893894271/p842393.png)
  
    - style of Giuseppe Arcimboldo, painting,oil,landscape,portrait,expressionism 适合人像
  
      ![image](https://help-static-aliyun-doc.aliyuncs.com/assets/img/zh-CN/2893894271/p842395.png)
  
    - style of Agostino Arrivabene, painting,oil,landscape,surrealism,italychao 超写实
  
      ![image](https://help-static-aliyun-doc.aliyuncs.com/assets/img/zh-CN/2893894271/p842396.png)
  
    - style of John James Audubon,ornithology,illustration,Haiti,19th century
  
      ![image](https://help-static-aliyun-doc.aliyuncs.com/assets/img/zh-CN/2893894271/p842397.png)
  
    - birds in the forest,style of Alice Bailly, painting,oil,tempera
  
      ![image](https://help-static-aliyun-doc.aliyuncs.com/assets/img/zh-CN/2893894271/p842399.png)
  
    - style of Olivier Bonhomme,illustration,france
  
      ![image](https://help-static-aliyun-doc.aliyuncs.com/assets/img/zh-CN/2893894271/p842400.png)
  
    - style of Henri-Edmond Cross,oil,painting,landscape,pointillism
  
      ![image](https://help-static-aliyun-doc.aliyuncs.com/assets/img/zh-CN/2893894271/p842402.png)
  
* 通用负面提示词
```markdown
((blurred)), ((disorderly)), ((bad art)), ((morbid)), ((Luminous)), out of frame, not clear, overexposure, lens flare, bokeh, jpeg artifacts, glowing light, (low quality:2.0),((black color)), shadowlowers, bad anatomy, ((bad hands)), (worst quality:2), (low quality:2), (normal quality:2), lowres, bad anatomy, text, error
```
###  SD Controlnet插件-线稿生成&高清修复

* Stable Diffusion模型（模型推荐：dreamshaper_8.safetensors）

> - **正向提示词：**
>
>   -  **画面内容描述：**
>
>     Green, Spring, Bamboo Forest, River:1.2, Flowing Water, Nature, Poetic Atmosphere, Green Theme, jade, light green
>
>   -  **提升画面质量：**
>
>     Masterpiece:1.2, Best Picture Quality, High Definition, Original, Extremely Good Wallpaper, Perfect Light, Extremely Good CG:1.2, Best Picture Quality, Magical Light Effect, super rich, super detailed, 32k, Abstract, 3D
>
>   - 调用LoRA模型 <lora:green:0.5> <lora:guofeng:0.3> <lora:shuimo:0.4>
>
> -  **反向提示词：**
>
>   lowres, bad anatomy, bad hands, text, error, missing fingers, extra digit, fewer digits, cropped, worst quality, low quality, normal quality, jpeg artifacts, signature, watermark, username, blurry
>
> - 参数:
>
>   - 迭代步数：30
>   - 采样方法：DPM++2M Karras
>   - 宽高：512*768
>   - 种子数：11806112（或者-1）

![Controlnet 例子](https://help-static-aliyun-doc.aliyuncs.com/assets/img/zh-CN/2961530371/p865541.jpeg)

>  **Controlnet1: Lineart （线稿）**
>
> - 选择Controlnet第一个tab选项
> - 上传一张图片
> - 依次选择绿色框内容，lineart 处理器coarse，ca49e26d, 权重0.8
> - 调整好参数与选项后，最后再点击小爆炸按钮
>
>  **Controlnet2: Depth（深度）**
>
> - 选择**Controlnet第二个tab**
> - 上传**与上面同样的图片**
> - 依次选择绿色框内容， Depth 处理器zoe，132477ea，权重0.3
> - 调整好参数与选项后，最后再点击小爆炸按钮



## 壁纸

* 正面提示词
```markdown
正向提示词
- 画面内容描述
Green, Spring, Bamboo Forest, River:1.2, Flowing Water, Nature, Poetic Atmosphere, Green Theme, jade, light green, 
- 提升画面质量
Masterpiece:1.2, Best Picture Quality, High Definition, Original, Extremely Good Wallpaper, Perfect Light, Extremely Good CG:1.2, Best Picture Quality, Magical Light Effect, super rich, super detailed, 32k, Abstract,
- 调用Lora模型
3D<lora:shuimo:0.5> <lora:green:0.1> <lora:guofeng:0.8>
```
* 负面提示词(举例)
```markdown
负向提示词
lowres, bad anatomy, bad hands, text, error, missing fingers, extra digit, fewer digits, cropped, worst quality, low quality, normal quality, jpeg artifacts, signature, watermark, username, blurry
```
> 迭代步数：30
> 	采样方法：DPM++2M Karras
> 	宽高：512*768
> 	种子数：-1

## 粘土风格
* 提示词:
```markdown
正向提示词：
1 girl, niantu,masterpiece,best quality <lora:niantuhua:1>（男生修改为“boy”：1 boy）

反向提示词：
badhandv4,paintings,sketches,(worst qualit:2),(low quality:2),(normal quality:2),lowers,normal quality,((monochrome)),((grayscale)),skin spots,acnes,skin blemishes,age spot,(outdoor:1.6),manboobs,(backlight:1.2),double navel,muted arms,hused arms,neck lace,analog,analog effects,(sunglass:1.4),nipples,nsfw,bad architecture,watermark,(mole:1.5),
```
参数:
> 其他参数设置
> 	重绘幅度设置为 0.7
> 	迭代步数：20
> 	采样方法：可以自己选择更换，尝试看效果

## 二次元风格

* 负向提示词:
```markdown
loli,nsfw,logo,text,badhandv4,EasyNegative,ng_deepnegative_v1_75t,rev2-badprompt,verybadimagenegative_v1.3,negative_hand-neg,mutated hands and fingers,poorly drawn face,extra limb,missing limb,disconnected limbs,malformed hands,ugly
```
## 形象创作

### Q版形象

>实验模型推荐：IPDesign3D
>
>-  **正向提示词（ip形象描述）：**
>
>  可直接复制：cute,child,full body, white background,(masterpiece:1.2), best quality, highres,extremely detailed CG,perfect lighting,8k wallpaper,
>
>-  **反向提示词：**
>
>  可直接复制：((blurred)), ((disorderly)), ((bad art)), ((morbid)), ((Luminous)), out of frame, not clear, overexposure, lens flare, bokeh, jpeg artifacts, glowing light, (low quality:2.0),((black color)), shadowlowers, bad anatomy, ((bad hands)), (worst quality:2), (low quality:2), (normal quality:2), lowres, bad anatomy, text, error
>
>- 通过xyz测试得出的该模型合适的步数为22，采样方法DPM++ 2M或者Euler a
>
>  **如果选择其他的模型请根据模型简介提示或者使用xyz测试进行步数测试**
>
>- 图片尺寸：采用512*768，生图后可通过高清修复进行尺寸扩展。
>
>- 打开高清修复，放大算法选择Latent，高分迭代步数11（是迭代步数的一半最佳），重绘幅度0.4
>
>- 填写准备好的白底黑边线稿的图片尺寸，尺寸如果大于1024，需要等比缩小填写
>
>- 填写提示词引导系数

### 特定动漫/二次元角色形象

> 模型推荐：AWPainting 、 万象熔炉|Anything V5/Ink（大模型）、Lora模型：Rem (Re:Zero)
>
> -  **正向提示词**（动漫形象描述）**：**
>
>   (masterpiece:1.2), best quality, highres,extremely detailed CG,perfect lighting,8k wallpaper
>
> -  **反向提示词：**
>
>   ((blurred)), ((disorderly)), ((bad art)), ((morbid)), ((Luminous)), out of frame, not clear, overexposure, lens flare, bokeh, jpeg artifacts, glowing light, (low quality:2.0),((black color)), shadowlowers, bad anatomy, ((bad hands)), (worst quality:2), (low quality:2), (normal quality:2), lowres, bad anatomy, text, error
>
> - Lora
>
>   * Lora模型：Rem (Re:Zero) 
>
>   * 角色定向模型：CJ_儿童绘本卡通插画
>
>   * 触发模型关键词：chibi
>
> - 参数选择
>
>   * 迭代部署：根据选择的大模型和Lora模型而定，下图为通过**xyz测试**得出的该模型Euler a为简约q版形象、DPM++2M采样下内容更详细。其采样迭代步数推荐分别为：26、22
>   * 打开高清修复，放大算法选择4x-UltraSharp，高分迭代步数11-13（是迭代步数的一半），重绘幅度0.4
>   * 填写准备好的白底黑边线稿的图片尺寸，尺寸如果大于1024，需要等比缩小填写
>   * 填写提示词引导系数

### 线稿上色

> 模型推荐：AWPainting 
>
> -  **正向提示词**（风格上色描述）**：**
>
>   可直接复制：(masterpiece:1.2), best quality, highres,extremely detailed CG,perfect lighting,8k wallpaper
>
> -  **反向提示词：**
>
>   可直接复制：((blurred)), ((disorderly)), ((bad art)), ((morbid)), ((Luminous)), out of frame, not clear, overexposure, lens flare, bokeh, jpeg artifacts, glowing light, (low quality:2.0),((black color)), shadowlowers, bad anatomy, ((bad hands)), (worst quality:2), (low quality:2), (normal quality:2), lowres, bad anatomy, text, error
>
> - Lora
>
>   Lora模型：Rem (Re:Zero) ，角色定向模型
>
> - 参数选择
>
>   * 迭代部署：20，根据选择的大模型和Lora模型而定，**如果选择其他的模型请根据模型简介提示或者使用xyz测试进行步数测试**
>   * 打开高清修复，放大算法选择4x-UltraSharp，高分迭代步数10（是迭代步数的一半），重绘幅度0.4
>   * 填写准备好的白底黑边线稿的图片尺寸，尺寸如果大于1024，需要等比缩小填写
>   * 填写提示词引导系数
>
> - 启用ControlNet
>
>   * 勾选启用、完美像素模式、允许预览
>   * 上传准备好的白底黑边线稿
>   * 控制类型选择Lineart（线稿）
>   * 点击爆炸图标即可预览线稿处理效果

## 多种艺术风格的logo创作

### 剪纸艺术风格logo

>
>
>- Lora:paper sculpture 权重0.6
>
>-  **正向提示词：**
>
>  Masterpiece,HD 8K,surreal frozen landscape,chinese surrealism,Kim Keever,cyan chinese dragon fantasy,paper art,(Blue and White:1.3),chinese art made of silk paper surreal frozen landscape chinese surrealism, <lora:paper sculpture:0.6>
>
>-  **反向提示词：**
>
>  ng_deepnegative_v1_75t,(badhandv4:1.2),EasyNegative,(worst quality:2),nsfw,
>
>- 参数:
>
>  - 采样方法：DPM++2Karras
>  - 迭代步数：20
>  - 高分辨率修复：4X-Ultrasharp
>  - 放大倍数：2
>  - 高分迭代步数：20
>  - 重绘幅度：0.4
>  - 单批数量：2
>  - 尺寸：768*512
>
>- ControlNet
>
>  - 完美像素模式
>
>  - 控制类型：选择Canny硬边缘，预处理器模型：control_v11p_sd15_canny [fcf10ca5]（此模型版本要与大模型版本一致）
>
>  - 控制权重：0.7
>
>  - 引导介入时机：0
>
>  - 引导终止时机：0.7

### LOGO艺术字海报

>
>
>- Stable Diffusion模型（模型推荐：revAnimated_v122）
>
>-  **正向提示词：**
>
>  Best quality,masterpieces,high resolution，Highly stylized,4k,Unreal Engine 5 rendering,volume light,atmospheric,crepuscular ray,Fujifilm Superia 400,natural light
>
>- **负向提示词：**
>
>  ((blurred)), ((disorderly)), ((bad art)), ((morbid)), ((Luminous)), out of frame, not clear, overexposure, lens flare, bokeh, jpeg artifacts, glowing light, (low quality:2.0),((black color)), shadowlowers, bad anatomy, ((bad hands)), (worst quality:2), (low quality:2), (normal quality:2), lowres, bad anatomy, text, error
>
>- Lora
>
>  - 电商草地场景(1.0 ～ 1.1)
>
>    grass,in a meadow,sky,water
>
>  -  ai_jidian_c4djingxichangjing(0.8)
>
>    science fiction, scenery, round stage
>
>  -  ai_jidian_guochaofeng(0.8)
>
>     lotus,Traditional Chinese architecture,mountain,cloud
>
>  - XSArchi_127(0.7~1)
>
>    machine,miniature,metal,mechanical
>
>- **ControlNet**
>
>  “启用”“完美像素模式” 、“允许预览” 。
>
>  在制作logo艺术字海报时，控制类型一般选择“Canny”，也可选择“Lineart”。如果想让生成图像中Logo更明确一些就可以将控制权重调高，或者在控制模式勾选“更偏向 ControlNet”。 

### 人工处理添加

>* 将logo添加到该图像中
>
>* Stable Diffusion模型（模型推荐：revAnimated_v122）
>
>* 重绘尺寸倍数以确保与原图比例相匹配。将重绘幅度设置在0.5左右。
>
>* Controlnet
>
>  “启用”“完美像素模式” 、控制类型选择Tile（分块）。
>
>  调低控制权重到0.6左右，引导终止时机到0.9左右，给ai留下生成空间以取得更好效果。


## 角色创作

### 2D转3D

>
>
>- Stable Diffusion模型:revAnimated_v122.safetensors
>
>- 参数调整
>
>  - 采样方式：Euler a
>  - 迭代步数：30
>  - 单批数量：4
>
>- 图片尺寸记得要更改到和原图尺寸大小一致
>
>-  ControlNet
>
>  启用、低显存模式、完美像素模式、Upload independent control image和允许预览
>
>  - Lineart线稿
>  - Depth深度，控制权重更改为0.85
>  - T2I-Adaper，预处理器选择色彩像素。
>
>- **正向提示词：**
>
>  A cartoon character with a breadhead, brown clothes, a smile, and a gray-black scarf，3D rendering, white background, simple background ,
>
>-  **反向提示词：**
>
>  lowres, bad anatomy, bad hands, text, error, missing fingers, extra digit,fewer digits, cropped, worst quality, low quality,normal quality, jpeg artifacts, signature,watermark, username, blurry,(worst quality:1.4),(low quality:1.4), (monochrome:1.1), Eagetive,
>
>- Lora:**blindbox_IP**

### 毛绒质感艺术风格

> - Stable Diffusion:realisticVisionV60B1_v51VAE.safetensors
>
> -  **参数**
>
>   - 迭代步数：30
>   - 宽度和高度：600
>   - 单批数量：4
>   - 提示词引导系数：5
>
> - ControlNet
>
>   启用、低显存模式、完美像素模式和允许预览
>
>   - Tile分块，控制权重改为0.5
>   - Softedge软边缘，控制权重更改为0.6。
>   - 全部,控制权重选择0.35,模型选择t2iadapter color_sd14v1
>
> -  **正向提示词：**
>
>   Masterpiece,topview,topview,(orange,white,fluffy,bijelo,plush,3D
>
>   art:1.4),solo,(placedonpurewhitebackground1.3),lightandshadow,studio
>
>   lighting,close-up,depthoffield,min-imalist,highQuality,HighDetail,SonyFE
>
>   GM,UHD,ConceptProd-，Woolfelt，Plush，maotuanzi，maotuanzi,Plush,Woolfelt，
>
> - **反向提示词：**
>
>   lowres,badanatomy,badhands,text,error,missingfingers,extradigit,fewer
>
>   digits,cropped,worstquality,lowquality,normalquality,jpegartifacts,
>
>   signature,watermark,username,blurry,(worstquality:1.4),(lowquality:1.4),
>
>   (monochrome:1.1),Eagetive,
>
> - Lora
>
>    **furryfelt** 和 **txtfurry**,0.6权重
>
> - 高分辨率修复
>
>   - 放大算法：R-ESRGAN 4x+
>   - 高分迭代步数：20
>   - 重绘幅度：0.3

## 风格迁移

>- Stable Diffusion模型（模型推荐：3Guofeng3_v32Light.safetensors）
>
>- CLIP终止层数选择2
>
>- **正向提示词（**「画面内容描述词」+「提升画面质量词」＋「调用LORA模型」**）：**
>
>  (best quality:1.2),ice cream,(white background:1.3),(ice cream:1.2),light green,pink,white,Macron tone,sarah saunders,blue background,illustratio,ice particles,snow,fluid,yotobi,pastelle,elaine benes,style of paolo parente,morearea,masterpiece,best quality,3D rendering, <lora:icecreamarchitecturelora1.0:0.8>
>
>- **负向提示词：**
>
>  light and shadow,, (worst quality:2),(low quality:2),(normal quality:2),lowres,bad anatomy,bad hands,((monochrome)),((grayscale)) watermark,moles,,nsfw
>
>- Lora:**冰淇淋质感**(0.6-0.8)
>
>- 参数调整:
>
>  - 采样方法：Euler a
>  - 开高分辨率：
>    - 放大算法选择4x-UltraSharp
>    - 高分迭代步数20-30
>    - 重绘幅度0.55
>    - 放大倍数2
>  - 长宽比：根据图生图改变
>
>- ControlNet
>
>  softEdge线稿控制，控制权重0.5，引导介入时机0，引导终止时机1。

# 图生图

> 采样器设置为“DPM++ 2M Karras”。
> 画面尺寸点击下面这个三角尺，可自动根据上传图片的此次填入，保证生成的图片与原图一致。
> 提示词引导系数修改为10。
> 重绘强度设置为0.5。
> 图像生成种子我们设置为“535240816”。

## 换背景

>
>
>- SD模型:laowang_ARCH_MIX_V0.5.safetensors
>
>- 图生图的Generation里选择上传重绘蒙版
>
>- 参数方面，迭代步数选择30，单批数量选择4
>
>- 图片尺寸记得要更改到和原图尺寸大小一致，点击三角尺的图标，自动更改尺寸
>
>- **正向提示词：**
>
>  Noon sunshine,sun,blue sky,cloud,(masterpiece), (high quality), best quality, real,(realistic), super detailed, (full detail),(4k),8k,scenery, outdoors,day,
>
>- **反向提示词：**
>
>  lowres, bad anatomy, bad hands, text, error, missing fingers, extra digit,fewer digits, cropped, worst quality, low quality,normal quality, jpeg artifacts, signature,watermark, username, blurry,(worst quality:1.4),(low quality:1.4), (monochrome:1.1), Eagetive,

## 室内家具换装

> - Stable Diffusion:laowang_ARCH_MIX_V0.5.safetensors
>
> - 图生图的Generation里选择局部重绘
>
> - 蒙版绘制:白色是蒙版部分
>
> - 参数:迭代步数选择30，单批数量选择4
>
> - 图片尺寸记得要更改到和原图尺寸大小一致，点击三角尺的图标，自动更改尺寸
>
>   - 正向提示词：
>
>     ((best quality)),((masterpiece)),((realistic)),leather sofa, limited palette background,from below
>
>   - 反向提示词：
>
>     3d, cartoon, lowres, bad anatomy, bad hands, text, error, missing fingers, extra digit, fewer digits, cropped,unrealisticdream,baddream,worst quality, low quality, normal quality, jpeg artifacts, signature, watermark, username, blurry, artist name, young, loli, elf, 3d, illustration
>
> - ControlNet
>
>   启用、低显存模式、完美像素模式、Upload independent control image和允许预览全部点击
>
>   IP-adapter，预处理器选择ip-adapter_clip_h。
>
>   模型选择ip-adapter-plus_sd15 [137e273c]，控制权重选择0.3
>
> - ControlNet(精准控制,图生图的Generation里选择上传重绘蒙版)
>
>   ControlNet，将启用、低显存模式、完美像素模式、Upload independent control image和允许预览全部点击
>
>   ControlNet的控制类型选择Lineart (线稿)
>
>   提示词如上

# 涂鸦绘制

> 缩放模式选择“拉伸”。
> 采样器选择“DPM++ 2M Karras”。
> 尺寸点击三角尺，匹配背景画布大小。
> 提示词引导系数设置为“10”。
> 图像重绘强度设置为“0.8”。
> 图像生成种子设置为“535260816”。

# LoRA模型训练

- 数据集图像收集：

至少十五张以上（选择高质量的图像数据，排除以下因素：水印，低清，怪异的光线，复杂且难以辨认的内容物，奇怪的角度等）。

> [!NOTE]
>
> **说明** **这里的高质量画面，主要指内容的高质量，画面清晰即可，无需尺寸过高。图像尺寸过高也会因为显存问题导致训练失败。以sd1.5基模的lora训练为例，图像像素在512\*512或者512\*768即可。**

- 数据集图像预处理：

  比如处理水印、文字、以及图像尺寸调整等，可以借助图像预处理工具裁剪为512×512尺寸即可（这里图像预处理软件大家可以用PS或者其它批量预处理图像的网站和软件）

- 新建数据集图像：

  创建数据集子文件夹：点击进入到新建的数据集里面，点击“新建文件夹”，文件夹命名格式为：“数字_任意名称”

  >  [!NOTE]
  >
  > **注意：命名格式为“数字_任意名称”，是工具对于训练数据集命名的要求。这里的数字，是指训练时赋予的repeat值，是通过文件夹命名来赋予的。图片数量 \* repeat 数量 \* 设置的epoch / batch_size = 训练总步。repeat数量指：训练过程中会读取多少次这个图像。**
  >
  > **注意：这里也可以本地准备好一个“数字_任意名称”的文件夹，然后直接上传到数据集下面。**


* 数据集图像批量打标

  utilities>WD14 Captioning(wD14标注)
  
  * undesired tags上写上自己不想要的提示词
  * Prefix to add to WD14 caption上写上你想要的Lora触发词
  
* 训练Lora的时候会需要一个checkpoint底模

  > [!NOTE]
  >
  > * Epoch（训练周期数）改为20
  >
  > - Max resolution（最大分辨率）改为768,768
  > - 取消勾选Enable buckets（数据集尺寸相同时取消勾选）
  > - Text Encoder learning rate（文本编码器学习率）改为0.00001
  > - Network Rank(Dimension)改为128；Network Alpha改为64。
  >
  > “loss值”是衡量模型预测与实际结果差异的关键指标。
  >
  > | 人物模型   | 0.06-0.09  |
  > | ---------- | ---------- |
  > | 实物模型在 | 0.07-0.09  |
  > | 风格模型   | 0.08-0.13  |
  > | 功能模型   | 0.003-0.05 |
