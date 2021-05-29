# Performance

## Hardware resources

Processor:	Intel(R) Core(TM) i7-4720HQ CPU @ 2.60GHz, 2594 Mhz, 4 Core(s), 8 Logical Processor(s)

Installed Physical Memory (RAM):	8.00 GB

Total Physical Memory:	7.89 GB


## Perfomance windows 10 64 bit

OS Name	Microsoft Windows 10 Home Single Language

Version	10.0.19042 Build 19042

## Thống kê
| Scheme | Operation Mode | Key Length | Iv Length | Total Encryption time | Average Encryption time | Total Decryption time | Average Decryption Time |
| ------    | -------------- | ---------- | ---------- | --------------------- | ----------------------- | -------------------- | ---------------------- |
| DES | CBC | | | | | | |
| DES | EBC | | | | | | |
| DES | CBC CTS | | | | | | |
| DES | CFB | | | | | | |
| DES | CTR | | | | | | |
| DES | OFB | | | | | | |
| AES | CBC | | | | | | |
| AES | CBC | | | | | | |
| AES |     | | | | | | |
| AES | CBC | | | | | | |
| AES | CBC | | | | | | |
| AES | CBC | | | | | | |
| AES | CBC | | | | | | |
| AES | CBC | | | | | | |
| AES | CBC | | | | | | |
| AES | CBC | | | | | | |
| AES | CBC | | | | | | |
| AES | CBC | | | | | | |

### DES with cryptopp library

#### CBC operation mode
![image](https://user-images.githubusercontent.com/31529599/120057225-a78cfa80-c06b-11eb-8951-ff2cd99ffc7d.png)


#### EBC operation mode
![image](https://user-images.githubusercontent.com/31529599/120057255-ea4ed280-c06b-11eb-8c76-99fce400cd1e.png)

#### CBC CTS operation mode
![image](https://user-images.githubusercontent.com/31529599/120057261-005c9300-c06c-11eb-94ae-18474e091b68.png)

#### CFB operation mode
![image](https://user-images.githubusercontent.com/31529599/120057301-3bf75d00-c06c-11eb-81ed-4005c5e7b191.png)

#### CTR operation mode
![image](https://user-images.githubusercontent.com/31529599/120057318-516c8700-c06c-11eb-83f4-0dc841044c7a.png)

#### OFB operation mode
![image](https://user-images.githubusercontent.com/31529599/120057328-5e897600-c06c-11eb-9f93-902a2828b4b7.png)


### AES with crypropp library

#### CBC operation mode
-> 128 bits key
![image](https://user-images.githubusercontent.com/31529599/120057373-ca6bde80-c06c-11eb-876b-f11095c91dc9.png)

-> 192 bits key
![image](https://user-images.githubusercontent.com/31529599/120057410-f9825000-c06c-11eb-803f-73b8cab0fc61.png)

-> 256 bits key
![image](https://user-images.githubusercontent.com/31529599/120057416-0c952000-c06d-11eb-92c8-f2a90204cb2f.png)


#### EBC operation mode
-> 128 bits key
![image](https://user-images.githubusercontent.com/31529599/120057438-38b0a100-c06d-11eb-95f0-3d0a6b2b2421.png)

-> 192 bits key
![image](https://user-images.githubusercontent.com/31529599/120057463-7281a780-c06d-11eb-82ea-074df5e899ed.png)

-> 256 bits key
![image](https://user-images.githubusercontent.com/31529599/120057480-a9f05400-c06d-11eb-890f-8396b2f94f92.png)



#### CBC CTS operation mode
-> 128 bits key
![image](https://user-images.githubusercontent.com/31529599/120057492-c1c7d800-c06d-11eb-8af5-10fcf189fe62.png)


-> 192 bits key
![image](https://user-images.githubusercontent.com/31529599/120057497-d4daa800-c06d-11eb-9f35-e3fb7e70fcef.png)


-> 256 bits key
![image](https://user-images.githubusercontent.com/31529599/120057509-e623b480-c06d-11eb-96d9-427910d7297f.png)


#### CFB operation mode
-> 128 bits key
![image](https://user-images.githubusercontent.com/31529599/120057524-005d9280-c06e-11eb-8864-8c9d64e50255.png)

-> 192 bits key
![image](https://user-images.githubusercontent.com/31529599/120057547-15d2bc80-c06e-11eb-901e-92f873a2e015.png)

-> 256 bits key
![image](https://user-images.githubusercontent.com/31529599/120057554-25ea9c00-c06e-11eb-9639-7e61732ce3d2.png)


#### CTR operation mode
-> 128 bits key
![image](https://user-images.githubusercontent.com/31529599/120057562-3ac72f80-c06e-11eb-8a31-07dae2b63b5a.png)

-> 192 bits key
![image](https://user-images.githubusercontent.com/31529599/120057578-503c5980-c06e-11eb-997d-06541bccc287.png)

-> 256 bits key
![image](https://user-images.githubusercontent.com/31529599/120057592-63e7c000-c06e-11eb-8659-5ff0d86d1d7b.png)


#### OFB operation mode
-> 128 bits key
![image](https://user-images.githubusercontent.com/31529599/120057685-38190a00-c06f-11eb-97a9-52a94d22f59b.png)

-> 192 bits key
![image](https://user-images.githubusercontent.com/31529599/120057693-436c3580-c06f-11eb-8e54-f5d22cfcada3.png)

-> 256 bits key
![image](https://user-images.githubusercontent.com/31529599/120057703-57179c00-c06f-11eb-981e-a0d044fdf1a8.png)



#### XTS operation mode
-> 256 bits key
![image](https://user-images.githubusercontent.com/31529599/120057725-8a5a2b00-c06f-11eb-806a-3efeab4da248.png)

-> 348 bits key
![image](https://user-images.githubusercontent.com/31529599/120057728-9645ed00-c06f-11eb-9d40-82245fab80bf.png)

-> 512 bits key
![image](https://user-images.githubusercontent.com/31529599/120057736-a5c53600-c06f-11eb-856f-94cde3a96d17.png)



#### GCM authentication operation mode
-> authentication data : ANTN2019

-> 128 bits key - iv 1000 bytes length
![image](https://user-images.githubusercontent.com/31529599/120057822-782cbc80-c070-11eb-82d9-534190ae8132.png)

-> 192 bits key
![image](https://user-images.githubusercontent.com/31529599/120057835-8e3a7d00-c070-11eb-873e-a533b7e7d759.png)

-> 256 bits key
![image](https://user-images.githubusercontent.com/31529599/120057842-a3171080-c070-11eb-9281-b41021bab535.png)



#### CCM authentication operation mode
-> authentication data : ANTN2019

-> 128 bits key - iv 10 bytes length
![image](https://user-images.githubusercontent.com/31529599/120057852-b88c3a80-c070-11eb-8d1b-7d394ec5e134.png)

-> 192 bits key
![image](https://user-images.githubusercontent.com/31529599/120057879-dfe30780-c070-11eb-8e52-8819e751180c.png)


-> 256 bits key
![image](https://user-images.githubusercontent.com/31529599/120057882-effae700-c070-11eb-973c-808634ec953b.png)


