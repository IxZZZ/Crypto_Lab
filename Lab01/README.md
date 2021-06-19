# Performance

## Hardware resources

Processor:	Intel(R) Core(TM) i7-4720HQ CPU @ 2.60GHz, 2594 Mhz, 4 Core(s), 8 Logical Processor(s)

Installed Physical Memory (RAM):	8.00 GB

Total Physical Memory:	7.89 GB


## Perfomance windows 10 64 bit

OS Name	Microsoft Windows 10 Home Single Language

Version	10.0.19042 Build 19042

## Thống kê (10000 vòng lặp)
| Scheme | Operation Mode | Key Length | Iv Length | Total Encryption Time ms (Windows) | Total Decryption Time ms (Windows) | Total Encryption Time ms (Linux) |Total Decryption Time ms (Linux) |
| ------    | -------------- | ---------- | ---------- | --------------------- | ----------------------- | -------------------- | ---------------------- |
| DES | CBC |64 |64 |123 |96 |107.87 |100.685 |
| DES | EBC | 64| 64| 114|105 |120.28 |102.772|
| DES | CBC CTS |64 | 64|131 |101 |118.048|101.909 |
| DES | CFB | 64|64 | 131|101 | 113.388|103.101 |
| DES | CTR |64 | 64| 124|112 | 150.037|109.551 |
| DES | OFB | 64| 64| 122|107 |113.256 |105.076 |
| AES | CBC |128 |128 |38 |21 | 19.176|17.777 |
| AES | CBC | 192|128 | 40|22 |43.897 |17.031 |
| AES | CBC | 256| 128| 38|29 | 24.551|17.843|
| AES | EBC | 128| n.a| 27|18 | 34.504|19.391 |
| AES | EBC | 192| n.a|29 | 16| 33.975|18.589 |
| AES | EBC | 256| n.a| 35|19 |29.083 |18.93 |
| AES | CBC CTS|128 | 128| 37|23 |32.654 |19.135 |
| AES | CBC CTS|192 | 128|38 |23 | 27.7| 19.166|
| AES | CBC CTS| 256|128 | 39|24 |30.504 |19.624 |
| AES | CFB |128| 128| 35| 22| 33.682| 20.856|
| AES | CFB |192| 128| 36|26 | 35.034|20.829 |
| AES | CFB |256|128 | 40| 16| 33.954| 22.35|
| AES | CTR |128| 128| 32| 25|49.484 | 35.045|
| AES | CTR |192| 128| 30|23 |23.877 |20.929 |
| AES | CTR |256|128 | 34|27 |28.616 |20.603 |
| AES | OFB |128| 128|37 |28 |32.19 | 16.322|
| AES | OFB |192| 128| 40|29 | 39.422|28.557 |
| AES | OFB |256|128 |44 | 31| 30.611|23.189 |
| AES | XTS |256| 128|41 |27 |30.611 |23.189 |
| AES | XTS |348| 128|40 | 26| 29.155|23.674 |
| AES | XTS |512|128 | 40|28 | 31.175| 24.758|
| AES | GCM |128| 1000| 33| 46| 36.056| 46.47|
| AES | GCM |192| 1000| 24| 46| 25.39|33.308 |
| AES | GCM |256|1000 |28 |48 |28.843|33.254 |
| AES | CCM |128| 10|36 |53 |37.963 |37.568 |
| AES | CCM |192| 10| 52|87 |34.64 |38.163 |
| AES | CCM |256|10 | 45|54 |35.784 |40.619 |

### DES with cryptopp library

#### CBC operation mode
windows:
![image](https://user-images.githubusercontent.com/31529599/120057225-a78cfa80-c06b-11eb-8951-ff2cd99ffc7d.png)
linux:
![image](https://user-images.githubusercontent.com/31529599/120061080-a36dd680-c085-11eb-91dd-8f48b02aaaee.png)


#### EBC operation mode
windows:
![image](https://user-images.githubusercontent.com/31529599/120057255-ea4ed280-c06b-11eb-8c76-99fce400cd1e.png)
linux:
![image](https://user-images.githubusercontent.com/31529599/120061102-be404b00-c085-11eb-9348-fcb42935b8c2.png)


#### CBC CTS operation mode
windows:
![image](https://user-images.githubusercontent.com/31529599/120057261-005c9300-c06c-11eb-94ae-18474e091b68.png)
linux:
![image](https://user-images.githubusercontent.com/31529599/120061116-d3b57500-c085-11eb-8191-73da91bb4ad7.png)

#### CFB operation mode
windows:
![image](https://user-images.githubusercontent.com/31529599/120057301-3bf75d00-c06c-11eb-81ed-4005c5e7b191.png)
linux:
![image](https://user-images.githubusercontent.com/31529599/120061147-05c6d700-c086-11eb-992d-5597585f6921.png)


#### CTR operation mode
windows:
![image](https://user-images.githubusercontent.com/31529599/120057318-516c8700-c06c-11eb-83f4-0dc841044c7a.png)
linux:
![image](https://user-images.githubusercontent.com/31529599/120061171-22fba580-c086-11eb-8979-6e58504f2122.png)


#### OFB operation mode
windows:
![image](https://user-images.githubusercontent.com/31529599/120057328-5e897600-c06c-11eb-9f93-902a2828b4b7.png)
linux:
![image](https://user-images.githubusercontent.com/31529599/120061182-3444b200-c086-11eb-8578-9c93ac9f8bef.png)



### AES with crypropp library

#### CBC operation mode
-> 128 bits key
windows:
![image](https://user-images.githubusercontent.com/31529599/120057373-ca6bde80-c06c-11eb-876b-f11095c91dc9.png)
linux:
![image](https://user-images.githubusercontent.com/31529599/120061228-6e15b880-c086-11eb-9151-b8ac14c82f0e.png)


-> 192 bits key
windows:
![image](https://user-images.githubusercontent.com/31529599/120057410-f9825000-c06c-11eb-803f-73b8cab0fc61.png)
linux:
![image](https://user-images.githubusercontent.com/31529599/120061257-91d8fe80-c086-11eb-8c28-c0376c6ce7a9.png)


-> 256 bits key
windows:
![image](https://user-images.githubusercontent.com/31529599/120057416-0c952000-c06d-11eb-92c8-f2a90204cb2f.png)
linux:
![image](https://user-images.githubusercontent.com/31529599/120061276-a917ec00-c086-11eb-9ad2-e6a0325565d9.png)



#### EBC operation mode
-> 128 bits key
windows:
![image](https://user-images.githubusercontent.com/31529599/120057438-38b0a100-c06d-11eb-95f0-3d0a6b2b2421.png)
linux:
![image](https://user-images.githubusercontent.com/31529599/120061430-6dc9ed00-c087-11eb-9296-d07db96bacd1.png)

-> 192 bits key
windows:
![image](https://user-images.githubusercontent.com/31529599/120057463-7281a780-c06d-11eb-82ea-074df5e899ed.png)
linux:
![image](https://user-images.githubusercontent.com/31529599/120061444-81755380-c087-11eb-9e7d-7a83abcdb49a.png)

-> 256 bits key
windows:
![image](https://user-images.githubusercontent.com/31529599/120057480-a9f05400-c06d-11eb-890f-8396b2f94f92.png)
linux:
![image](https://user-images.githubusercontent.com/31529599/120061518-dc0eaf80-c087-11eb-85d7-5468e1650857.png)

#### CBC CTS operation mode
-> 128 bits key
windows:
![image](https://user-images.githubusercontent.com/31529599/120057492-c1c7d800-c06d-11eb-8af5-10fcf189fe62.png)
linux:
![image](https://user-images.githubusercontent.com/31529599/120061534-e92b9e80-c087-11eb-9242-8eac44ff8cbd.png)


-> 192 bits key
windows:
![image](https://user-images.githubusercontent.com/31529599/120057497-d4daa800-c06d-11eb-9f35-e3fb7e70fcef.png)
linux:
![image](https://user-images.githubusercontent.com/31529599/120061540-f183d980-c087-11eb-9558-981b9accb0d5.png)


-> 256 bits key
windows:
![image](https://user-images.githubusercontent.com/31529599/120057509-e623b480-c06d-11eb-96d9-427910d7297f.png)
linux:
![image](https://user-images.githubusercontent.com/31529599/120061561-07919a00-c088-11eb-847e-959a201d0572.png)

#### CFB operation mode
-> 128 bits key
windows:
![image](https://user-images.githubusercontent.com/31529599/120057524-005d9280-c06e-11eb-8864-8c9d64e50255.png)
linux:
![image](https://user-images.githubusercontent.com/31529599/120061579-21cb7800-c088-11eb-95ca-66bba997bb3d.png)

-> 192 bits key
windows:
![image](https://user-images.githubusercontent.com/31529599/120057547-15d2bc80-c06e-11eb-901e-92f873a2e015.png)
linux:
![image](https://user-images.githubusercontent.com/31529599/120061586-2728c280-c088-11eb-92da-c932d38110c6.png)

-> 256 bits key
windows:
![image](https://user-images.githubusercontent.com/31529599/120057554-25ea9c00-c06e-11eb-9639-7e61732ce3d2.png)
linux:
![image](https://user-images.githubusercontent.com/31529599/120061596-2f80fd80-c088-11eb-8f7c-f21c8caa5884.png)

#### CTR operation mode
-> 128 bits key
windows:
![image](https://user-images.githubusercontent.com/31529599/120057562-3ac72f80-c06e-11eb-8a31-07dae2b63b5a.png)
linux:
![image](https://user-images.githubusercontent.com/31529599/120061672-7ff85b00-c088-11eb-8fd8-b69cc4d33a35.png)

-> 192 bits key
windows:
![image](https://user-images.githubusercontent.com/31529599/120057578-503c5980-c06e-11eb-997d-06541bccc287.png)
linux:
![image](https://user-images.githubusercontent.com/31529599/120061688-8ab2f000-c088-11eb-9131-84551acc1c10.png)

-> 256 bits key
windows:
![image](https://user-images.githubusercontent.com/31529599/120057592-63e7c000-c06e-11eb-8659-5ff0d86d1d7b.png)
linux:
![image](https://user-images.githubusercontent.com/31529599/120061690-930b2b00-c088-11eb-86b0-8b630e0efd7f.png)


#### OFB operation mode
-> 128 bits key
windows:
![image](https://user-images.githubusercontent.com/31529599/120057685-38190a00-c06f-11eb-97a9-52a94d22f59b.png)
linux:
![image](https://user-images.githubusercontent.com/31529599/120061711-a6b69180-c088-11eb-8a6f-6bbafc4a65dc.png)

-> 192 bits key
windows:
![image](https://user-images.githubusercontent.com/31529599/120057693-436c3580-c06f-11eb-8e54-f5d22cfcada3.png)
linux:
![image](https://user-images.githubusercontent.com/31529599/120061718-af0ecc80-c088-11eb-900d-744a87a7bc0f.png)

-> 256 bits key
windows:
![image](https://user-images.githubusercontent.com/31529599/120057703-57179c00-c06f-11eb-981e-a0d044fdf1a8.png)
linux:
![image](https://user-images.githubusercontent.com/31529599/120061726-b7ff9e00-c088-11eb-8951-77f1c037458a.png)


#### XTS operation mode
-> 256 bits key
windows:
![image](https://user-images.githubusercontent.com/31529599/120057725-8a5a2b00-c06f-11eb-806a-3efeab4da248.png)
linux:
![image](https://user-images.githubusercontent.com/31529599/120061772-ebdac380-c088-11eb-8e5e-210ff39b3405.png)

-> 348 bits key
windows:
![image](https://user-images.githubusercontent.com/31529599/120057728-9645ed00-c06f-11eb-9d40-82245fab80bf.png)
linux:
![image](https://user-images.githubusercontent.com/31529599/120061755-d5cd0300-c088-11eb-89c9-29fceb2acf7f.png)

-> 512 bits key
windows:
![image](https://user-images.githubusercontent.com/31529599/120057736-a5c53600-c06f-11eb-856f-94cde3a96d17.png)
linux:
![image](https://user-images.githubusercontent.com/31529599/120061760-dcf41100-c088-11eb-9bc1-487ae0309157.png)


#### GCM authentication operation mode
-> authentication data : ANTN2019

-> 128 bits key - iv 1000 bytes length
windows:
![image](https://user-images.githubusercontent.com/31529599/120057822-782cbc80-c070-11eb-82d9-534190ae8132.png)
linux:
![image](https://user-images.githubusercontent.com/31529599/120062173-f302d100-c08a-11eb-83af-4e8635e2508f.png)

-> 192 bits key
windows:
![image](https://user-images.githubusercontent.com/31529599/120057835-8e3a7d00-c070-11eb-873e-a533b7e7d759.png)
linux:
![image](https://user-images.githubusercontent.com/31529599/120062188-0746ce00-c08b-11eb-9220-7eb8d9a68098.png)

-> 256 bits key
windows:
![image](https://user-images.githubusercontent.com/31529599/120057842-a3171080-c070-11eb-9281-b41021bab535.png)
linux:
![image](https://user-images.githubusercontent.com/31529599/120062207-22194280-c08b-11eb-9add-bbf54696b8c6.png)


#### CCM authentication operation mode
-> authentication data : ANTN2019

-> 128 bits key - iv 10 bytes length
windows:
![image](https://user-images.githubusercontent.com/31529599/120057852-b88c3a80-c070-11eb-8d1b-7d394ec5e134.png)
linux:
![image](https://user-images.githubusercontent.com/31529599/120062233-46751f00-c08b-11eb-8446-2870076696e5.png)

-> 192 bits key
windows:
![image](https://user-images.githubusercontent.com/31529599/120057879-dfe30780-c070-11eb-8e52-8819e751180c.png)
linux:
![image](https://user-images.githubusercontent.com/31529599/120062239-4f65f080-c08b-11eb-9cad-b7f954a243de.png)

-> 256 bits key
windows:
![image](https://user-images.githubusercontent.com/31529599/120057882-effae700-c070-11eb-973c-808634ec953b.png)
linux:
![image](https://user-images.githubusercontent.com/31529599/120062250-58ef5880-c08b-11eb-98d1-b3938036fbe3.png)
