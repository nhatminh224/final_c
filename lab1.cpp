#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <float.h>

#define MAX_NAME 50
#define MAX_ID 20
#define MAX_ADDRESS 100
#define MAX_STUDENTS 1000
#define DATA_FILE "data.txt"

// Cau truc diem cua mot thi sinh
typedef struct {
    float toan;
    float ly;
    float hoa;
    float sinh;
    float van;
    float anh;
    float tong;
} DiemThi;

// Cau truc thong tin thi sinh
typedef struct {
    char maThiSinh[MAX_ID];
    char hoTen[MAX_NAME];
    char ngaySinh[15];
    char diaChi[MAX_ADDRESS];
    int gioiTinh; // 0: Nam, 1: Nu
    DiemThi diem;
} ThiSinh;

// Cau truc node cho danh sach lien ket
typedef struct Node {
    ThiSinh data;
    struct Node* next;
} Node;

// Khai bao con tro dau cua danh sach lien ket
Node* head = NULL;

// Bien toan cuc de luu so luong thi sinh hien tai
int soLuongThiSinh = 0;

// Mang con tro de luu danh sach thi sinh (su dung song song voi DSLK)
ThiSinh* danhSachThiSinh[MAX_STUDENTS];

// Ham de xoa buffer stdin
void clearInputBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// Ham de tam dung man hinh
void tamDung() {
    printf("\nNhan Enter de tiep tuc...");
    clearInputBuffer();
    getchar();
}

// Ham tao node moi
Node* taoNode(ThiSinh thiSinh) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (newNode == NULL) {
        printf("Loi cap phat bo nho!\n");
        return NULL;
    }
    newNode->data = thiSinh;
    newNode->next = NULL;
    return newNode;
}

// Ham them thi sinh vao cuoi danh sach lien ket
void themThiSinh(ThiSinh thiSinh) {
    Node* newNode = taoNode(thiSinh);
    if (newNode == NULL) return;
    
    // Them vao danh sach lien ket
    if (head == NULL) {
        head = newNode;
    } else {
        Node* current = head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = newNode;
    }
    
    // Them vao mang con tro
    if (soLuongThiSinh < MAX_STUDENTS) {
        // Cap phat bo nho dong cho thi sinh moi
        danhSachThiSinh[soLuongThiSinh] = (ThiSinh*)malloc(sizeof(ThiSinh));
        if (danhSachThiSinh[soLuongThiSinh] != NULL) {
            *danhSachThiSinh[soLuongThiSinh] = thiSinh;
            soLuongThiSinh++;
        }
    } else {
        printf("Mang da day, khong the them thi sinh moi!\n");
    }
}

// Ham nhap thong tin thi sinh moi tu ban phim
ThiSinh nhapThiSinh() {
    ThiSinh thiSinh;
    
    printf("\n==== NHAP THONG TIN THI SINH ====\n");
    
    // Kiem tra ma thi sinh trung lap
    int maTrung;
    do {
        maTrung = 0;
        printf("Ma thi sinh: ");
        scanf("%s", thiSinh.maThiSinh);
        
        // Kiem tra trung
        Node* current = head;
        while (current != NULL) {
            if (strcmp(current->data.maThiSinh, thiSinh.maThiSinh) == 0) {
                printf("Ma thi sinh da ton tai! Vui long nhap lai.\n");
                maTrung = 1;
                break;
            }
            current = current->next;
        }
    } while (maTrung);
    
    clearInputBuffer();
    printf("Ho ten: ");
    fgets(thiSinh.hoTen, MAX_NAME, stdin);
    thiSinh.hoTen[strcspn(thiSinh.hoTen, "\n")] = 0; // Xoa ky tu xuong dong
    
    printf("Ngay sinh (DD/MM/YYYY): ");
    scanf("%s", thiSinh.ngaySinh);
    
    clearInputBuffer();
    printf("Dia chi: ");
    fgets(thiSinh.diaChi, MAX_ADDRESS, stdin);
    thiSinh.diaChi[strcspn(thiSinh.diaChi, "\n")] = 0; // Xoa ky tu xuong dong
    
    printf("Gioi tinh (0: Nam, 1: Nu): ");
    scanf("%d", &thiSinh.gioiTinh);
    
    printf("\n-- NHAP DIEM THI --\n");
    printf("Diem Toan: ");
    scanf("%f", &thiSinh.diem.toan);
    
    printf("Diem Ly: ");
    scanf("%f", &thiSinh.diem.ly);
    
    printf("Diem Hoa: ");
    scanf("%f", &thiSinh.diem.hoa);
    
    printf("Diem Sinh: ");
    scanf("%f", &thiSinh.diem.sinh);
    
    printf("Diem Van: ");
    scanf("%f", &thiSinh.diem.van);
    
    printf("Diem Anh: ");
    scanf("%f", &thiSinh.diem.anh);
    
    // Tinh tong diem
    thiSinh.diem.tong = thiSinh.diem.toan + thiSinh.diem.ly + thiSinh.diem.hoa + 
                        thiSinh.diem.sinh + thiSinh.diem.van + thiSinh.diem.anh;
    
    return thiSinh;
}

// Ham hien thi thong tin cua mot thi sinh
void hienThiThiSinh(ThiSinh ts) {
    printf("| %-10s | %-20s | %-12s | %-5s | %-30s | %5.2f | %5.2f | %5.2f | %5.2f | %5.2f | %5.2f | %6.2f |\n",
           ts.maThiSinh, ts.hoTen, ts.ngaySinh, 
           ts.gioiTinh == 0 ? "Nam" : "Nu", ts.diaChi,
           ts.diem.toan, ts.diem.ly, ts.diem.hoa, 
           ts.diem.sinh, ts.diem.van, ts.diem.anh, ts.diem.tong);
}

// Ham hien thi tat ca thi sinh trong danh sach
void hienThiDanhSachThiSinh() {
    if (head == NULL) {
        printf("\nDanh sach thi sinh trong!\n");
        return;
    }
    
    printf("\n=====================================================================================================================================================\n");
    printf("| %-10s | %-20s | %-12s | %-5s | %-30s | %-5s | %-5s | %-5s | %-5s | %-5s | %-5s | %-6s |\n",
           "Ma TS", "Ho ten", "Ngay sinh", "GT", "Dia chi", "Toan", "Ly", "Hoa", "Sinh", "Van", "Anh", "Tong");
    printf("\n=====================================================================================================================================================\n");
    
    // Su dung con tro de duyet danh sach lien ket
    Node* current = head;
    while (current != NULL) {
        hienThiThiSinh(current->data);
        current = current->next;
    }
    
    printf("\n======================================================================================================================================================\n");
}

// Ham tim kiem thi sinh theo ma
Node* timKiemTheoMa(char* ma) {
    Node* current = head;
    while (current != NULL) {
        if (strcmp(current->data.maThiSinh, ma) == 0) {
            return current;
        }
        current = current->next;
    }
    return NULL;
}

// Ham sua thong tin thi sinh
void suaThongTinThiSinh() {
    if (head == NULL) {
        printf("\nDanh sach thi sinh trong!\n");
        return;
    }
    
    char ma[MAX_ID];
    printf("\nNhap ma thi sinh can sua: ");
    scanf("%s", ma);
    
    Node* thiSinh = timKiemTheoMa(ma);
    if (thiSinh == NULL) {
        printf("\nKhong tim thay thi sinh co ma %s!\n", ma);
        return;
    }
    
    printf("\nThong tin thi sinh truoc khi sua:\n");
    printf("======================================================================================================================================================\n");
    printf("| %-10s | %-20s | %-12s | %-5s | %-30s | %-5s | %-5s | %-5s | %-5s | %-5s | %-5s | %-6s |\n",
           "Ma TS", "Ho ten", "Ngay sinh", "GT", "Dia chi", "Toan", "Ly", "Hoa", "Sinh", "Van", "Anh", "Tong");
    printf("======================================================================================================================================================\n");
    hienThiThiSinh(thiSinh->data);
    printf("======================================================================================================================================================\n");
    
    int luaChon;
    do {
        printf("\n---- MENU SUA THONG TIN ----\n");
        printf("1. Sua ho ten\n");
        printf("2. Sua ngay sinh\n");
        printf("3. Sua dia chi\n");
        printf("4. Sua gioi tinh\n");
        printf("5. Sua diem\n");
        printf("0. Quay lai menu chinh\n");
        printf("Chon thong tin can sua: ");
        scanf("%d", &luaChon);
        
        switch (luaChon) {
            case 1:
                clearInputBuffer();
                printf("Nhap ho ten moi: ");
                fgets(thiSinh->data.hoTen, MAX_NAME, stdin);
                thiSinh->data.hoTen[strcspn(thiSinh->data.hoTen, "\n")] = 0;
                break;
            case 2:
                printf("Nhap ngay sinh moi (DD/MM/YYYY): ");
                scanf("%s", thiSinh->data.ngaySinh);
                break;
            case 3:
                clearInputBuffer();
                printf("Nhap dia chi moi: ");
                fgets(thiSinh->data.diaChi, MAX_ADDRESS, stdin);
                thiSinh->data.diaChi[strcspn(thiSinh->data.diaChi, "\n")] = 0;
                break;
            case 4:
                printf("Nhap gioi tinh moi (0: Nam, 1: Nu): ");
                scanf("%d", &thiSinh->data.gioiTinh);
                break;
            case 5:
                printf("Nhap diem Toan moi: ");
                scanf("%f", &thiSinh->data.diem.toan);
                
                printf("Nhap diem Ly moi: ");
                scanf("%f", &thiSinh->data.diem.ly);
                
                printf("Nhap diem Hoa moi: ");
                scanf("%f", &thiSinh->data.diem.hoa);
                
                printf("Nhap diem Sinh moi: ");
                scanf("%f", &thiSinh->data.diem.sinh);
                
                printf("Nhap diem Van moi: ");
                scanf("%f", &thiSinh->data.diem.van);
                
                printf("Nhap diem Anh moi: ");
                scanf("%f", &thiSinh->data.diem.anh);
                
                // Cap nhat tong diem
                thiSinh->data.diem.tong = thiSinh->data.diem.toan + thiSinh->data.diem.ly + 
                                         thiSinh->data.diem.hoa + thiSinh->data.diem.sinh + 
                                         thiSinh->data.diem.van + thiSinh->data.diem.anh;
                break;
            case 0:
                printf("Quay lai menu chinh.\n");
                break;
            default:
                printf("Lua chon khong hop le!\n");
        }
        
        if (luaChon > 0 && luaChon <= 5) {
            printf("\nDa cap nhat thong tin thi sinh thanh cong!\n");
            
            // Cap nhat thong tin trong mang con tro
            for (int i = 0; i < soLuongThiSinh; i++) {
                if (strcmp(danhSachThiSinh[i]->maThiSinh, ma) == 0) {
                    *danhSachThiSinh[i] = thiSinh->data;
                    break;
                }
            }
        }
    } while (luaChon != 0);
}

// Ham xoa thi sinh theo ma
void xoaThiSinh() {
    if (head == NULL) {
        printf("\nDanh sach thi sinh trong!\n");
        return;
    }
    
    char ma[MAX_ID];
    printf("\nNhap ma thi sinh can xoa: ");
    scanf("%s", ma);
    
    // Truong hop dac biet: xoa node dau tien
    if (strcmp(head->data.maThiSinh, ma) == 0) {
        Node* temp = head;
        head = head->next;
        free(temp);
        
        // Cap nhat mang con tro
        int indexToRemove = -1;
        for (int i = 0; i < soLuongThiSinh; i++) {
            if (strcmp(danhSachThiSinh[i]->maThiSinh, ma) == 0) {
                indexToRemove = i;
                free(danhSachThiSinh[i]);
                break;
            }
        }
        
        if (indexToRemove != -1) {
            // Dich chuyen cac phan tu sau vi tri xoa len
            for (int i = indexToRemove; i < soLuongThiSinh - 1; i++) {
                danhSachThiSinh[i] = danhSachThiSinh[i + 1];
            }
            soLuongThiSinh--;
        }
        
        printf("\nDa xoa thi sinh co ma %s!\n", ma);
        return;
    }
    
    // Tim node truoc node can xoa
    Node* current = head;
    while (current->next != NULL && strcmp(current->next->data.maThiSinh, ma) != 0) {
        current = current->next;
    }
    
    if (current->next == NULL) {
        printf("\nKhong tim thay thi sinh co ma %s!\n", ma);
        return;
    }
    
    // Xoa node khoi danh sach lien ket
    Node* temp = current->next;
    current->next = temp->next;
    free(temp);
    
    // Cap nhat mang con tro
    int indexToRemove = -1;
    for (int i = 0; i < soLuongThiSinh; i++) {
        if (strcmp(danhSachThiSinh[i]->maThiSinh, ma) == 0) {
            indexToRemove = i;
            free(danhSachThiSinh[i]);
            break;
        }
    }
    
    if (indexToRemove != -1) {
        // Dich chuyen cac phan tu sau vi tri xoa len
        for (int i = indexToRemove; i < soLuongThiSinh - 1; i++) {
            danhSachThiSinh[i] = danhSachThiSinh[i + 1];
        }
        soLuongThiSinh--;
    }
    
    printf("\nDa xoa thi sinh co ma %s!\n", ma);
}

// Ham tim kiem thi sinh theo ten
void timKiemTheoTen() {
    if (head == NULL) {
        printf("\nDanh sach thi sinh trong!\n");
        return;
    }
    
    char ten[MAX_NAME];
    clearInputBuffer();
    printf("\nNhap ten thi sinh can tim: ");
    fgets(ten, MAX_NAME, stdin);
    ten[strcspn(ten, "\n")] = 0; // Xoa ky tu xuong dong
    
    // Chuyen ten sang chu thuong de tim kiem khong phan biet hoa thuong
    for (int i = 0; ten[i]; i++) {
        ten[i] = tolower(ten[i]);
    }
    
    printf("\n======================================================================================================================================================\n");
    printf("| %-10s | %-20s | %-12s | %-5s | %-30s | %-5s | %-5s | %-5s | %-5s | %-5s | %-5s | %-6s |\n",
           "Ma TS", "Ho ten", "Ngay sinh", "GT", "Dia chi", "Toan", "Ly", "Hoa", "Sinh", "Van", "Anh", "Tong");
    printf("======================================================================================================================================================\n");
    
    int found = 0;
    Node* current = head;
    while (current != NULL) {
        char tenHoaSo[MAX_NAME];
        strcpy(tenHoaSo, current->data.hoTen);
        
        // Chuyen ten hien tai sang chu thuong
        for (int i = 0; tenHoaSo[i]; i++) {
            tenHoaSo[i] = tolower(tenHoaSo[i]);
        }
        
        // Tim kiem khong phan biet hoa thuong
        if (strstr(tenHoaSo, ten) != NULL) {
            hienThiThiSinh(current->data);
            found = 1;
        }
        current = current->next;
    }
    
    printf("======================================================================================================================================================\n");
    
    if (!found) {
        printf("\nKhong tim thay thi sinh nao co ten chua '%s'!\n", ten);
    }
}

// Ham sap xep thi sinh theo tong diem (giam dan) - Bubble Sort
void sapXepTheoDiem() {
    if (soLuongThiSinh <= 1) {
        return;
    }
    
    // Su dung Bubble Sort voi mang con tro
    for (int i = 0; i < soLuongThiSinh - 1; i++) {
        for (int j = 0; j < soLuongThiSinh - i - 1; j++) {
            if (danhSachThiSinh[j]->diem.tong < danhSachThiSinh[j + 1]->diem.tong) {
                // Hoan doi chi con tro, khong phai du lieu
                ThiSinh* temp = danhSachThiSinh[j];
                danhSachThiSinh[j] = danhSachThiSinh[j + 1];
                danhSachThiSinh[j + 1] = temp;
            }
        }
    }
    
    // Cap nhat lai danh sach lien ket tu mang da sap xep
    if (soLuongThiSinh > 0) {
        // Xoa danh sach lien ket cu
        Node* current = head;
        while (current != NULL) {
            Node* next = current->next;
            free(current);
            current = next;
        }
        
        // Tao lai danh sach lien ket tu mang da sap xep
        head = NULL;
        for (int i = 0; i < soLuongThiSinh; i++) {
            Node* newNode = taoNode(*danhSachThiSinh[i]);
            
            if (head == NULL) {
                head = newNode;
            } else {
                Node* last = head;
                while (last->next != NULL) {
                    last = last->next;
                }
                last->next = newNode;
            }
        }
    }
}

// Ham thong ke diem theo khoi thi
void thongKeTheoDiem() {
    if (head == NULL) {
        printf("\nDanh sach thi sinh trong!\n");
        return;
    }
    
    // Tim diem cao nhat va thap nhat
    float diemCaoNhat = -1.0;
    float diemThapNhat = FLT_MAX;
    
    Node* current = head;
    while (current != NULL) {
        float tongDiem = current->data.diem.tong;
        
        if (tongDiem > diemCaoNhat) {
            diemCaoNhat = tongDiem;
        }
        
        if (tongDiem < diemThapNhat) {
            diemThapNhat = tongDiem;
        }
        
        current = current->next;
    }
    
    printf("\n============ THONG KE DIEM THI ============\n");
    printf("Tong so thi sinh: %d\n", soLuongThiSinh);
    
    // Hien thi thi sinh co diem cao nhat
    printf("\n--- THI SINH CO DIEM CAO NHAT (%.2f diem) ---\n", diemCaoNhat);
    printf("======================================================================================================================================================\n");
    printf("| %-10s | %-20s | %-12s | %-5s | %-30s | %-5s | %-5s | %-5s | %-5s | %-5s | %-5s | %-6s |\n",
           "Ma TS", "Ho ten", "Ngay sinh", "GT", "Dia chi", "Toan", "Ly", "Hoa", "Sinh", "Van", "Anh", "Tong");
    printf("======================================================================================================================================================\n");
    
    current = head;
    while (current != NULL) {
        if (current->data.diem.tong == diemCaoNhat) {
            hienThiThiSinh(current->data);
        }
        current = current->next;
    }
    
    printf("======================================================================================================================================================\n");
    
    // Hien thi thi sinh co diem thap nhat
    printf("\n--- THI SINH CO DIEM THAP NHAT (%.2f diem) ---\n", diemThapNhat);
    printf("======================================================================================================================================================\n");
    printf("| %-10s | %-20s | %-12s | %-5s | %-30s | %-5s | %-5s | %-5s | %-5s | %-5s | %-5s | %-6s |\n",
           "Ma TS", "Ho ten", "Ngay sinh", "GT", "Dia chi", "Toan", "Ly", "Hoa", "Sinh", "Van", "Anh", "Tong");
    printf("======================================================================================================================================================\n");
    
    current = head;
    while (current != NULL) {
        if (current->data.diem.tong == diemThapNhat) {
            hienThiThiSinh(current->data);
        }
        current = current->next;
    }
    
    printf("======================================================================================================================================================\n");
    
    // Thong ke phan bo diem
    // int duoi15 = 0, tu15den20 = 0, tu20den25 = 0, tren25 = 0;
    
    // current = head;
    // while (current != NULL) {
    //     float tongDiem = current->data.diem.tong;
        
    //     if (tongDiem < 15.0) {
    //         duoi15++;
    //     } else if (tongDiem >= 15.0 && tongDiem < 20.0) {
    //         tu15den20++;
    //     } else if (tongDiem >= 20.0 && tongDiem < 25.0) {
    //         tu20den25++;
    //     } else {
    //         tren25++;
    //     }
        
    //     current = current->next;
    // }
    
    // printf("\n--- PHAN BO DIEM ---\n");
    // printf("So thi sinh co tong diem duoi 15: %d (%.2f%%)\n", 
    //        duoi15, soLuongThiSinh > 0 ? (float)duoi15 * 100 / soLuongThiSinh : 0);
    // printf("So thi sinh co tong diem tu 15 den duoi 20: %d (%.2f%%)\n", 
    //        tu15den20, soLuongThiSinh > 0 ? (float)tu15den20 * 100 / soLuongThiSinh : 0);
    // printf("So thi sinh co tong diem tu 20 den duoi 25: %d (%.2f%%)\n", 
    //        tu20den25, soLuongThiSinh > 0 ? (float)tu20den25 * 100 / soLuongThiSinh : 0);
    // printf("So thi sinh co tong diem tu 25 tro len: %d (%.2f%%)\n", 
    //        tren25, soLuongThiSinh > 0 ? (float)tren25 * 100 / soLuongThiSinh : 0);
}

// Ham xuat danh sach thi sinh trung tuyen theo diem chuan
void xuatDanhSachTrungTuyen() {
    if (head == NULL) {
        printf("\nDanh sach thi sinh trong!\n");
        return;
    }
    
    float diemChuan;
    printf("\nNhap diem chuan: ");
    scanf("%f", &diemChuan);
    
    printf("\n================ DANH SACH THI SINH TRUNG TUYEN ================\n");
    printf("Diem chuan: %.2f\n\n", diemChuan);
    
    printf("======================================================================================================================================================\n");
    printf("| %-5s | %-10s | %-30s | %-12s | %-5s | %-30s | %-5s | %-5s | %-5s | %-5s | %-5s | %-5s | %-6s |\n",
           "STT", "Ma TS", "Ho ten", "Ngay sinh", "GT", "Dia chi", "Toan", "Ly", "Hoa", "Sinh", "Van", "Anh", "Tong");
    printf("======================================================================================================================================================\n");
    
    int stt = 1;
    int soLuongTrungTuyen = 0;
    
    // Sap xep theo diem truoc khi xuat
    sapXepTheoDiem();
    
    Node* current = head;
    while (current != NULL) {
        if (current->data.diem.tong >= diemChuan) {
            printf("| %-5d ", stt++);
            hienThiThiSinh(current->data);
            soLuongTrungTuyen++;
        }
        current = current->next;
    }
    
    printf("======================================================================================================================================================\n");
    printf("\nTong so thi sinh trung tuyen: %d\n", soLuongTrungTuyen);
    printf("Ty le trung tuyen: %.2f%%\n", soLuongThiSinh > 0 ? (float)soLuongTrungTuyen * 100 / soLuongThiSinh : 0);
}

// Ham luu danh sach thi sinh ra file
void luuDanhSachRaFile() {
    if (head == NULL) {
        printf("\nDanh sach thi sinh trong, khong co gi de luu!\n");
        return;
    }
    
    FILE *fp = fopen(DATA_FILE, "w");
    if (fp == NULL) {
        printf("Khong the mo file %s de ghi!\n", DATA_FILE);
        return;
    }
    
    // Ghi header
    fprintf(fp, "Ma TS,Ho ten,Ngay sinh,Gioi tinh,Dia chi,Toan,Ly,Hoa,Sinh,Van,Anh,Tong diem\n");
    
    // Ghi du lieu thi sinh
    Node* current = head;
    while (current != NULL) {
        ThiSinh ts = current->data;
        fprintf(fp, "%s,%s,%s,%s,%s,%.2f,%.2f,%.2f,%.2f,%.2f,%.2f,%.2f\n",
                ts.maThiSinh, ts.hoTen, ts.ngaySinh,
                ts.gioiTinh == 0 ? "Nam" : "Nu", ts.diaChi,
                ts.diem.toan, ts.diem.ly, ts.diem.hoa,
                ts.diem.sinh, ts.diem.van, ts.diem.anh, ts.diem.tong);
        current = current->next;
    }
    
    fclose(fp);
    printf("\nDa luu danh sach thi sinh vao file '%s' thanh cong!\n", DATA_FILE);
}

// Ham doc danh sach thi sinh tu file
void docDanhSachTuFile() {
    FILE *fp = fopen(DATA_FILE, "r");
    if (fp == NULL) {
        printf("Khong the mo file %s de doc!\n", DATA_FILE);
        return;
    }
    
    // Xoa danh sach hien tai neu co
    Node* current = head;
    while (current != NULL) {
        Node* temp = current;
        current = current->next;
        free(temp);
    }
    head = NULL;
    
    // Giai phong bo nho cua mang con tro
    for (int i = 0; i < soLuongThiSinh; i++) {
        free(danhSachThiSinh[i]);
    }
    soLuongThiSinh = 0;
    
    char line[500];
    // Doc va bo qua dong header
    fgets(line, sizeof(line), fp);
    
    // Doc tung dong du lieu
    while (fgets(line, sizeof(line), fp)) {
        ThiSinh ts;
        char gioiTinhStr[10];
        
        // Su dung strtok de phan tach du lieu
        char *token = strtok(line, ",");
        if (token != NULL) strcpy(ts.maThiSinh, token);
        
        token = strtok(NULL, ",");
        if (token != NULL) strcpy(ts.hoTen, token);
        
        token = strtok(NULL, ",");
        if (token != NULL) strcpy(ts.ngaySinh, token);
        
        token = strtok(NULL, ",");
        if (token != NULL) {
            strcpy(gioiTinhStr, token);
            ts.gioiTinh = (strcmp(gioiTinhStr, "Nam") == 0) ? 0 : 1;
        }
        
        token = strtok(NULL, ",");
        if (token != NULL) strcpy(ts.diaChi, token);
        
        token = strtok(NULL, ",");
        if (token != NULL) ts.diem.toan = atof(token);
        
        token = strtok(NULL, ",");
        if (token != NULL) ts.diem.ly = atof(token);
        
        token = strtok(NULL, ",");
        if (token != NULL) ts.diem.hoa = atof(token);
        
        token = strtok(NULL, ",");
        if (token != NULL) ts.diem.sinh = atof(token);
        
        token = strtok(NULL, ",");
        if (token != NULL) ts.diem.van = atof(token);
        
        token = strtok(NULL, ",");
        if (token != NULL) ts.diem.anh = atof(token);
        
        // Tinh tong diem
        ts.diem.tong = ts.diem.toan + ts.diem.ly + ts.diem.hoa + 
                       ts.diem.sinh + ts.diem.van + ts.diem.anh;
        
        // Them thi sinh vao danh sach
        themThiSinh(ts);
    }
    
    fclose(fp);
    printf("\nDa doc danh sach thi sinh tu file '%s' thanh cong!\n", DATA_FILE);
    printf("Tong so thi sinh da nap vao chuong trinh: %d\n", soLuongThiSinh);
}

// Ham giai phong bo nho khi ket thuc chuong trinh
void giaiPhongBoNho() {
    // Giai phong danh sach lien ket
    Node* current = head;
    while (current != NULL) {
        Node* temp = current;
        current = current->next;
        free(temp);
    }
    
    // Giai phong mang con tro
    for (int i = 0; i < soLuongThiSinh; i++) {
        free(danhSachThiSinh[i]);
    }
    
    printf("\nDa giai phong bo nho thanh cong!\n");
}

// Ham hien thi menu chinh
void hienThiMenu() {
    printf("\n=== CHUONG TRINH QUAN LY DIEM THI DAI HOC ===\n");
    printf("1. Them thi sinh moi\n");
    printf("2. Hien thi danh sach thi sinh\n");
    printf("3. Tim kiem thi sinh theo ma\n");
    printf("4. Tim kiem thi sinh theo ten\n");
    printf("5. Sua thong tin thi sinh\n");
    printf("6. Xoa thi sinh\n");
    printf("7. Sap xep thi sinh theo tong diem\n");
    printf("8. Thong ke diem\n");
    printf("9. Xuat danh sach thi sinh trung tuyen\n");
    printf("10. Luu danh sach ra file\n");
    printf("11. Doc danh sach tu file\n");
    printf("0. Thoat\n");
    printf("Chon chuc nang: ");
}

int main() {
    int luaChon;
    
    do {
        hienThiMenu();
        scanf("%d", &luaChon);
        
        switch (luaChon) {
            case 1:
                themThiSinh(nhapThiSinh());
                printf("\nDa them thi sinh moi thanh cong!\n");
                tamDung();
                break;
            case 2:
                hienThiDanhSachThiSinh();
                tamDung();
                break;
            case 3: {
                char ma[MAX_ID];
                printf("\nNhap ma thi sinh can tim: ");
                scanf("%s", ma);
                
                Node* thiSinh = timKiemTheoMa(ma);
                if (thiSinh != NULL) {
                    printf("\nThong tin thi sinh tim thay:\n");
                    printf("======================================================================================================================================================\n");
                    printf("| %-10s | %-20s | %-12s | %-5s | %-30s | %-5s | %-5s | %-5s | %-5s | %-5s | %-5s | %-6s |\n",
                           "Ma TS", "Ho ten", "Ngay sinh", "GT", "Dia chi", "Toan", "Ly", "Hoa", "Sinh", "Van", "Anh", "Tong");
                    printf("======================================================================================================================================================\n");
                    hienThiThiSinh(thiSinh->data);
                    printf("======================================================================================================================================================\n");
                } else {
                    printf("\nKhong tim thay thi sinh co ma %s!\n", ma);
                }
                tamDung();
                break;
            }
            case 4:
                timKiemTheoTen();
                tamDung();
                break;
            case 5:
                suaThongTinThiSinh();
                tamDung();
                break;
            case 6:
                xoaThiSinh();
                tamDung();
                break;
            case 7:
                sapXepTheoDiem();
                printf("\nDa sap xep danh sach thi sinh theo tong diem giam dan!\n");
                tamDung();
                break;
            case 8:
                thongKeTheoDiem();
                tamDung();
                break;
            case 9:
                xuatDanhSachTrungTuyen();
                tamDung();
                break;
            case 10:
                luuDanhSachRaFile();
                tamDung();
                break;
            case 11:
                docDanhSachTuFile();
                tamDung();
                break;
            case 0:
                printf("\nDang thoat chuong trinh...\n");
                giaiPhongBoNho();
                printf("Cam on da su dung chuong trinh!\n");
                break;
            default:
                printf("\nLua chon khong hop le! Vui long chon lai.\n");
                tamDung();
        }
    } while (luaChon != 0);
    
    return 0;
}
