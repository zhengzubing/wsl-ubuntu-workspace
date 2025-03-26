#include "include/core/SkCanvas.h"
#include "include/core/SkData.h"
#include "include/core/SkPaint.h"
#include "include/core/SkPath.h"
#include "include/core/SkStream.h"
#include "include/core/SkSurface.h"

void drawTriangle(SkCanvas* canvas) {
    SkPaint paint;
    paint.setColor(SK_ColorBLACK);
    paint.setStyle(SkPaint::kFill_Style);

    SkPath path;
    path.moveTo(100, 100);  // 第一个顶点
    path.lineTo(150, 200);  // 第二个顶点
    path.lineTo(50, 200);   // 第三个顶点
    path.close();           // 关闭路径

    canvas->drawPath(path, paint);
}

int main() {
    auto surface = SkSurface::MakeRasterN32Premul(300, 300);
    SkCanvas* canvas = surface->getCanvas();

    drawTriangle(canvas);

    // 保存图像到文件
    sk_sp<SkImage> image = surface->makeImageSnapshot();
    sk_sp<SkData> pngData =
        image->encodeToData(SkEncodedImageFormat::kPNG, 100);
    SkFILEWStream out("triangle.png");
    out.write(pngData->data(), pngData->size());

    return 0;
}