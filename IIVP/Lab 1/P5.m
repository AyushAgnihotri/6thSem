clear;
clc;
r = input('Enter no. of rows: ')
c = input('Enter no. of columns: ')

for i = 1:r
    for j = 1:c
        if mod(i, 2) == 0    
            if mod(j, 2) == 0
                check_box(i, j) = 0;
            else
                check_box(i, j) = 255;
            end
        else
            if mod(j, 2) == 0
                check_box(i, j) = 255;
            else
                check_box(i, j) = 0;
            end
        end
    end
end
imshow(check_box);