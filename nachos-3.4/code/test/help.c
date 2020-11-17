#include "syscall.h"

int main()
{
	PrintString("***** Thong tin gioi thieu nhom *****\n1712895 - Tran Thi Diem Uyen\n18120258 - Tran Thanh Tung\n18120288 - Tran Huu Chi Bao\n18120293 - Vong Canh Chi\n18120296 - Cao Tat Cuong\n");
	PrintString("***** Mo ta chuong trinh sort *****\nNhap vao mang n phan tu (nguoi dung nhap n <= 100, sai thi yeu cau nhap lai).\n");
	PrintString("Tiep theo nguoi dung co 2 lua chon la sap xep giam (nhap 0) hay sap xep tang (nhap 1) (nguoi dung nhap sai thi yeu cau nhap lai).\n");
	PrintString("Ham sort su dung thuat toan bubble sort de sap xep mang tren sau do in ra mang da sap xep theo yeu cau cua nguoi dung.\n");
	PrintString("***** Mo ta chuong trinh ascii *****\nDung ham PrintChar de in ra cac ky tu cua bang ma ascii tu ky tu 33 den 126 (cac ky tu co the doc duoc).\n");
	return 0;
}
