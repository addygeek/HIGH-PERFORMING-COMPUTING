BEGIN {
    max_x = 1.0; min_x = -1.0;
    max_y = 1.0; min_y = -1.0;
    width = 80; height = 20;
}

{
    x = int((( $1 - min_x) / (max_x - min_x)) * width);
    y = int((( $2 - min_y) / (max_y - min_y)) * height);
    if (x >= 0 && x < width && y >= 0 && y < height) {
        plot[y, x] = "*";
    }
}

END {
    for (y = height-1; y >= 0; y--) {
        for (x = 0; x < width; x++) {
            if (plot[y, x]) {
                printf("%s", plot[y, x]);
            } else {
                printf(" ");
            }
        }
        print "";
    }
}
