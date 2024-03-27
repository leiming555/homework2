#include <stdio.h>

// 灰度直方图均衡化函数
void equalize_histogram(unsigned char image[8][8]) {
    int histogram[256] = {0}; // 初始化直方图

    // 计算直方图
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            histogram[image[i][j]]++;
        }
    }

    // 计算累积直方图
    int cumulative_histogram[256] = {0};
    cumulative_histogram[0] = histogram[0];
    for (int i = 1; i < 256; ++i) {
        cumulative_histogram[i] = cumulative_histogram[i - 1] + histogram[i];
    }

    // 计算映射表
    unsigned char mapping_table[256];
    for (int i = 0; i < 256; ++i) {
        mapping_table[i] = (unsigned char)(((float)cumulative_histogram[i] / 64) * 255);
    }

    // 应用映射表到图像数据
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            image[i][j] = mapping_table[image[i][j]];
        }
    }
}

int main() {
    // 原始图像矩阵
    unsigned char image[8][8] = {
        {1,   5,   255, 225, 100, 200, 255, 200},
        {1,   7,   254, 255, 100, 10,  10,  9},
        {3,   7,   10,  100, 100, 2,   9,   6},
        {3,   6,   10,  10,  9,   2,   8,   2},
        {2,   1,   8,   8,   9,   3,   4,   2},
        {1,   0,   7,   8,   8,   3,   2,   1},
        {1,   1,   8,   8,   7,   2,   2,   1},
        {2,   3,   9,   8,   7,   2,   2,   0}
    };

    // 对图像进行直方图均衡化处理
    equalize_histogram(image);

    // 打印处理后的图像数据
    printf("Processed Image:\n");
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            printf("%3d ", image[i][j]);
        }
        printf("\n");
    }

    return 0;
}
