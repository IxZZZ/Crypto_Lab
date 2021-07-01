# Task 1: Two collision messages have the same prefix string


## tạo file prefix
Tạo file prefix với 64 ký tự (63 ký tự 'A' và 1 ký tự kết thúc chuỗi)

```bash
 python -c "print('A'*63)" > collision_text.txt
```

![image](https://user-images.githubusercontent.com/31529599/124090096-b9a0f500-da7e-11eb-8f5f-b8e842710870.png)

## Chạy collision với `md5collgen`:

![image](https://user-images.githubusercontent.com/31529599/124090176-c7ef1100-da7e-11eb-8557-bc78507d9ef8.png)

## Kiểm tra collision của 2 file

![image](https://user-images.githubusercontent.com/31529599/124090304-ea812a00-da7e-11eb-8ee7-c0e8225fa1f6.png)


## Kiểm tra sự khác nhau của hai file

![image](https://user-images.githubusercontent.com/31529599/124090487-18ff0500-da7f-11eb-97b4-c67b44a83d3a.png)

![image](https://user-images.githubusercontent.com/31529599/124090553-24eac700-da7f-11eb-912d-924da1f0fce9.png)

# Seed lab report

```c
#include <iostream>

unsigned char xyz[200] = {
    0x41, 0x41, 0x41, 0x41, 0x41, 0x41, 0x41, 0x41, 0x41, 0x41, 0x41, 0x41, 0x41, 0x41, 0x41, 0x41, 0x41, 0x41, 0x41, 0x41, 0x41, 0x41, 0x41, 0x41, 0x41, 0x41, 0x41, 0x41, 0x41, 0x41, 0x41, 0x41, 0x41, 0x41, 0x41, 0x41, 0x41, 0x41, 0x41, 0x41, 0x41, 0x41, 0x41, 0x41, 0x41, 0x41, 0x41, 0x41, 0x41, 0x41, 0x41, 0x41, 0x41, 0x41, 0x41, 0x41, 0x41, 0x41, 0x41, 0x41, 0x41, 0x41, 0x41, 0x41, 0x41, 0x41, 0x41, 0x41, 0x41, 0x41, 0x41, 0x41, 0x41, 0x41, 0x41, 0x41, 0x41, 0x41, 0x41, 0x41, 0x41, 0x41, 0x41, 0x41, 0x41, 0x41, 0x41, 0x41, 0x41, 0x41, 0x41, 0x41, 0x41, 0x41, 0x41, 0x41, 0x41, 0x41, 0x41, 0x41, 0x41, 0x41, 0x41, 0x41, 0x41, 0x41, 0x41, 0x41, 0x41, 0x41, 0x41, 0x41, 0x41, 0x41, 0x41, 0x41, 0x41, 0x41, 0x41, 0x41, 0x41, 0x41, 0x41, 0x41, 0x41, 0x41, 0x41, 0x41, 0x41, 0x41, 0x41, 0x41, 0x41, 0x41, 0x41, 0x41, 0x41, 0x41, 0x41, 0x41, 0x41, 0x41, 0x41, 0x41, 0x41, 0x41, 0x41, 0x41, 0x41, 0x41, 0x41, 0x41, 0x41, 0x41, 0x41, 0x41, 0x41, 0x41, 0x41, 0x41, 0x41, 0x41, 0x41, 0x41, 0x41, 0x41, 0x41, 0x41, 0x41, 0x41, 0x41, 0x41, 0x41, 0x41, 0x41, 0x41, 0x41, 0x41, 0x41, 0x41, 0x41, 0x41, 0x41, 0x41, 0x41, 0x41, 0x41, 0x41, 0x41, 0x41, 0x41, 0x41, 0x41, 0x41, 0x41, 0x41, 0x41, 0x41, 0x41, 0x41};

int main()
{
    for (int i = 0; i < 200; i++)
    {
        std::cout << xyz[i] << " ";
    }
    std::cout << std::endl;
}
```


## Compile program chạy thử chương trình

![image](https://user-images.githubusercontent.com/31529599/124091129-b22e1b80-da7f-11eb-876f-88f770f8b02d.png)

![image](https://user-images.githubusercontent.com/31529599/124093666-4305f680-da82-11eb-8039-08ae98b72197.png)

## Cách khai thác

![image](https://user-images.githubusercontent.com/31529599/124091915-83fd0b80-da80-11eb-9fc3-a0b7f2e27cc4.png)


## Tạo prefix 

Tìm vị trí của mảng `xyz` chia hết cho `64`:

![image](https://user-images.githubusercontent.com/31529599/124091302-e1dd2380-da7f-11eb-889f-e10f0d456d4b.png)

vị trí của mảng [0x3060-0x3028]

=> vị trí kết thúc của prefix sẽ là 0x3080 % 64 == 0 

`0x3080 = 12416`

![image](https://user-images.githubusercontent.com/31529599/124092386-fe2d9000-da80-11eb-890d-ff6cbf0d7f58.png)


## Tạo suffix 

Phần collision sẽ có độ dài `128` bytes, nên phần suffix sẽ từ vị trí kết thúc của prefix cộng với 128 bytes (12416 + 128 = 12544)

![image](https://user-images.githubusercontent.com/31529599/124092936-9297f280-da81-11eb-935b-a2343915d842.png)


## Chạy collision để generate ra hai file P và Q

![image](https://user-images.githubusercontent.com/31529599/124093322-f1f60280-da81-11eb-9159-803493d7dcb4.png)


Lấy phần P, Q 128 bit từ 2 file collision vừa mới được tạo:

![image](https://user-images.githubusercontent.com/31529599/124093484-1e118380-da82-11eb-8a11-95f224e266ee.png)


## Nối prefix , P/Q , suffix lại với nhau 

![image](https://user-images.githubusercontent.com/31529599/124093840-68930000-da82-11eb-9e46-9c63004e0575.png)

-> Chạy 2 file collision: 

![image](https://user-images.githubusercontent.com/31529599/124093864-6df04a80-da82-11eb-8886-c3541733ab28.png)


## Kiểm tra hash md5 của 2 file

![image](https://user-images.githubusercontent.com/31529599/124094000-8e200980-da82-11eb-9e1d-f397d5a4a5ca.png)



# Task 2 : Chosen prefix attack - hai file code khác nhau có cùng hash md5

Code chương trình 1:

```c
#include <stdio.h>
int main()
{
    printf("GoodGood Program !!\n");
}
```

Code chương trình 2: 

```c
#include <stdio.h>
int main()
{
    printf("Bad Program !!\n");
}
```

## compile thành 2 file thực thi

![image](https://user-images.githubusercontent.com/31529599/124094693-3766ff80-da83-11eb-883d-b14a86ceb2cb.png)


![image](https://user-images.githubusercontent.com/31529599/124094745-3fbf3a80-da83-11eb-9da7-41ab41c29321.png)

## Chạy hai file thực thi 
![image](https://user-images.githubusercontent.com/31529599/124095074-8ca31100-da83-11eb-9663-749e324c33d7.png)

## Chạy tool hashclash - chosen prefix attack
![image](https://user-images.githubusercontent.com/31529599/124094780-4a79cf80-da83-11eb-8e43-994ad72b3845.png)

## Kết quả

thời gian chạy => gần 18h

![image](https://user-images.githubusercontent.com/31529599/124094823-536aa100-da83-11eb-964a-c32ab6f033f8.png)

![image](https://user-images.githubusercontent.com/31529599/124095000-7c8b3180-da83-11eb-966c-ced89800760a.png)


## kiểm tra hash md5

-> md5 của 2 file sau khi chạy collision:

![image](https://user-images.githubusercontent.com/31529599/124095329-c4aa5400-da83-11eb-939f-a837202b3372.png)

-> md5 của 2 file ban đầu:

![image](https://user-images.githubusercontent.com/31529599/124095412-d7bd2400-da83-11eb-867a-4ab3684a49c0.png)
