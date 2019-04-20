// Des.cpp: implementation of the CMyDes class.
//用数组计算，实现

#include <stdlib.h>
#include <string.h>
#include "MyDes.h"

#define UCHAR unsigned char

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

/*CMyDes::CMyDes(CString strin, CString strkey, bool mode)
{
	m_len = strin.GetLength();
	m_len = (m_len+7)/8*8;

	m_src = (UCHAR*)malloc(m_len+9);
	memset(m_src, 0, m_len+9);
	memcpy(m_src, strin.GetBuffer(0), strin.GetLength());

	m_des = (UCHAR*)malloc(m_len+9);
	memset(m_des, 0, m_len+9);

	m_key = (UCHAR*)malloc(8+1);
	memset(m_key, 0, 8+1);
	memcpy(m_key, strkey.GetBuffer(0), strkey.GetLength()>8?8:strkey.GetLength());

	m_mode = mode;
}*/

CMyDes::CMyDes(char* pIn, int len, char*pKey, bool mode)
{
	m_len = len;
	m_len = (m_len+7)/8*8;
	
	m_src = (UCHAR*)malloc(m_len+9);
	memset(m_src, 0, m_len+9);
	memcpy(m_src, pIn, m_len);
	
	m_des = (UCHAR*)malloc(m_len+9);
	memset(m_des, 0, m_len+9);
	
	m_key = (UCHAR*)malloc(8+1);
	memset(m_key, 0, 8+1);
	memcpy(m_key, pKey, strlen(pKey)>8?8:strlen(pKey));
	
	m_mode = mode;
}

CMyDes::~CMyDes()
{
	free(m_src);
	free(m_des);
	free(m_key);
}

int CMyDes::DoDes(unsigned char *p)
{
	for(int i=0; i<m_len/8; i++)
	{
		des(&m_src[i*8], &m_des[i*8], m_key, m_mode);
	}
	strncpy((char*)p, (char*)m_des, m_len);
	return m_len;
}

/*void CMyDes::DoDes(CString &strout)
{
	for(int i=0; i<m_len/8; i++)
	{
		des(&m_src[i*8], &m_des[i*8], m_key, m_mode);
	}
	strout = CString((LPCTSTR )m_des, m_len);
}*/


/* ================================================================
des()
Description: DES algorithm,do encript or descript.
================================================================ */
void CMyDes::des(UCHAR*source, UCHAR* dest, UCHAR* keyin, bool flg)
{
	UCHAR key[64], key_cd[56], keyi[48];
	UCHAR data_buf[64], data_tmp[64], work_buf[48], work_tmp[48];
	register i, j, k, iter;
	

	//密钥转换: 64bit->64bit
	for (i=0; i<8; i++) 
	{
		for (k=0; k<8; k++)
			key[8*i+k] = *(keyin+i) >> (7-k) & 1;
	}
	//密钥pc1转换: 64b->56b, Permutation Choice 1 of Key
	static UCHAR tb_pc1_key[56] = //Permutated Choice 1 of key, 64->56
	{
       57, 49, 41, 33, 25, 17,  9,  1, 58, 50, 42, 34, 26, 18,
       10,  2, 59, 51, 43, 35, 27, 19, 11,  3, 60, 52, 44, 36,
       63, 55, 47, 39, 31, 23, 15,  7, 62, 54, 46, 38, 30, 22,
       14,  6, 61, 53, 45, 37, 29, 21, 13,  5, 28, 20, 12,  4
	};
	for ( i=0; i<56; i++)
		key_cd[i] = key[tb_pc1_key[i]-1];
	//这里没有再去计算所有的新秘钥，开始先算明文数据

	
	//数据转换: 64bit->64bit
	for (i = 0; i < 8; i++) 
	{
		for (k=0; k<8; k++)
			data_tmp[8*i+k] = *(source+i) >> (7-k) & 1;
	}
	//数据IP转换: 64b->64b, Initial Permutation of Data
	static UCHAR  tb_ip1[64] = //Initial Permutation of Data, 64->64
	{
		58, 50, 42, 34, 26, 18, 10, 2, 60, 52, 44, 36, 28, 20, 12, 4,
        62, 54, 46, 38, 30, 22, 14, 6, 64, 56, 48, 40, 32, 24, 16, 8,
        57, 49, 41, 33, 25, 17,  9, 1, 59, 51, 43, 35, 27, 19, 11, 3,
        61, 53, 45, 37, 29, 21, 13, 5, 63, 55, 47, 39, 31, 23, 15, 7 
	};
	for (i=0; i<64; i++)
		data_buf[i] = data_tmp[tb_ip1[i]-1];


	//数据加密迭代, 16 Iterations 
	for (iter = 1; iter < 17; iter++)
	{
		//生成单次key
		//移位
		static UCHAR key_shift[16] = {1, 1, 2, 2, 2, 2, 2, 2, 1, 2, 2, 2, 2, 2, 2, 1 };	/* Table - Shift */
		if (flg==true) //Encrption, shift left
		//说明一下，因为key第一位存的是最左边的数
		{
			for (i=0; i<(int)key_shift[iter-1]; i++) 
			{
				UCHAR temp1 = key_cd[0], temp2 = key_cd[28]; 
				for (j = 0; j < 27; j++) 
				{
					key_cd[j]    = key_cd[j+ 1];
					key_cd[j+28] = key_cd[j+29];
				}
				key_cd[27] = temp1; 	key_cd[55] = temp2;
			}
		} 
		else if (iter>1) //Decryption, shift right, 第一次不移动
		{
			for (i=0; i<(int)key_shift[17-iter]; i++) 
			{
				UCHAR temp1 = key_cd[27], temp2 = key_cd[55];
				for (j = 27; j > 0; j--) 
				{
					key_cd[j]    = key_cd[j-1];
					key_cd[j+28] = key_cd[j+27];
				}
				key_cd[0]  = temp1;		key_cd[28] = temp2;
			
			}
		}

		//密钥pc2转换: 56b->48b, Permutation Choice 2 of Key
		static UCHAR pc2_key[48] = //Permutated Choice 2 of key, 56->48
		{
			14, 17, 11, 24,  1,  5,  3, 28, 15,  6, 21, 10,
			23, 19, 12,  4, 26,  8, 16,  7, 27, 20, 13,  2,
			41, 52, 31, 37, 47, 55, 30, 40, 51, 45, 33, 48,
			44, 49, 39, 56, 34, 53, 46, 42, 50, 36, 29, 32
		};
		for (i=0; i<48; i++)
			keyi[i] = key_cd[pc2_key[i]-1];


		//数据处理F函数
		//右半边数据，因为E函数处理的是右边
		for (i = 0; i < 32; i++)
		{
			work_tmp[i] = data_buf[32+i];
		}

		//数据扩展函数E，32b->48b，Permute - E
		static UCHAR tb_e[48] = //32b -> 扩展48b
		{
            32,1,2,3,4,5,4,5,6,7,8,9,
			8,9,10,11,12,13,12,13,14,15,16,17,
			16,17,18,19,20,21,20,21,22,23,24,25,
			24,25,26,27,28,29,28,29,30,31,32,1 
		};
		//感觉下面的步骤污染了work_buf……
		for (i=0; i<48; i++)
			work_buf[i] = work_tmp[tb_e[i]-1];


		//数据加密处理：work_buf XOR keyi
		for (i = 0; i < 48; i++)
			work_buf[i] = work_buf[i] ^ keyi[i];

		//数据S-BOX处理，8 s-functions 
		static UCHAR s_box[8][4][16] = 
		{
			/* Table - s1 */
			{
				14,4,13,1,2,15,11,8,3,10,6,12,5,9,0,7,
				 0,15,7,4,14,2,13,1,10,6,12,11,9,5,3,8,
				 4,1,14,8,13,6,2,11,15,12,9,7,3,10,5,0,
				15,12,8,2,4,9,1,7,5,11,3,14,10,0,6,13 
			},
			/* Table - s2 */
			{
				15,1,8,14,6,11,3,4,9,7,2,13,12,0,5,10,
				 3,13,4,7, 15,  2,  8, 14, 12, 0,  1, 10,  6, 9, 11,  5,
				 0, 14,  7, 11, 10,  4, 13,  1,  5, 8, 12,  6,  9, 3,  2, 15,
				13,  8, 10,  1,  3, 15,  4,  2, 11, 6,  7, 12,  0, 5, 14,  9 
			},
			/* Table - s3 */
			{
				10,  0,  9, 14, 6,  3, 15,  5,  1, 13, 12,  7, 11,  4,  2, 8,
				13,  7,  0,  9, 3,  4,  6, 10,  2,  8,  5, 14, 12, 11, 15, 1,
				13,  6,  4,  9, 8, 15,  3,  0, 11,  1,  2, 12,  5, 10, 14, 7,
				 1, 10, 13,  0, 6,  9,  8,  7,  4, 15, 14,  3, 11,  5,  2, 12 
			},
			/* Table - s4 */
			{
				 7, 13, 14, 3,  0,  6,  9, 10,  1, 2, 8,  5, 11, 12,  4, 15,
				13,  8, 11, 5,  6, 15,  0,  3,  4, 7, 2, 12,  1, 10, 14,  9,
				10,  6,  9, 0, 12, 11,  7, 13, 15, 1, 3, 14,  5,  2,  8,  4,
				 3, 15,  0, 6, 10,  1, 13,  8,  9, 4, 5, 11, 12,  7,  2, 14 
			},
			/* Table - s5 */
			{
				 2, 12,  4,  1,  7, 10, 11,  6,  8,  5,  3, 15, 13, 0, 14,  9,
				14, 11,  2, 12,  4,  7, 13,  1,  5,  0, 15, 10,  3, 9,  8,  6,
				 4,  2,  1, 11, 10, 13,  7,  8, 15,  9, 12,  5,  6, 3,  0, 14,
				11,  8, 12,  7,  1, 14,  2, 13,  6, 15,  0,  9, 10, 4,  5,  3
			},
			/* Table - s6 */
			{
				12,  1, 10, 15, 9,  2,  6,  8,  0, 13,  3,  4, 14,  7,  5, 11,
				10, 15,  4,  2, 7, 12,  9,  5,  6,  1, 13, 14,  0, 11,  3, 8,
				 9, 14, 15,  5, 2,  8, 12,  3,  7,  0,  4, 10,  1, 13, 11, 6,
				 4,  3,  2, 12, 9,  5, 15, 10, 11, 14,  1,  7,  6,  0,  8, 13 
			},
			/* Table - s7 */
			{
				 4, 11,  2, 14, 15, 0,  8, 13,  3, 12, 9,  7,  5, 10, 6, 1,
				13,  0, 11,  7,  4, 9,  1, 10, 14,  3, 5, 12,  2, 15, 8, 6,
				 1,  4, 11, 13, 12, 3,  7, 14, 10, 15, 6,  8,  0,  5, 9, 2,
				 6, 11, 13,  8,  1, 4, 10,  7,  9,  5, 0, 15, 14,  2, 3, 12 
			},
			/* Table - s8 */
			{
				13,  2,  8, 4,  6, 15, 11,  1, 10,  9,  3, 14,  5,  0, 12, 7,
				 1, 15, 13, 8, 10,  3,  7,  4, 12,  5,  6, 11,  0, 14,  9, 2,
				 7, 11,  4, 1,  9, 12, 14,  2,  0,  6, 10, 13, 15,  3,  5, 8,
				 2,  1, 14, 7,  4, 10,  8, 13, 15, 12,  9,  0,  3,  5,  6, 11 
			}
		};
		for (i=0; i<8; i++)
		{
			//j把6个比特的收尾拼接，00-11
			j = work_buf[0+6*i]*2 + work_buf[5+6*i];
			//k把6个比特的中间拼接，0000-1111
			k = work_buf[1+6*i]*8 + work_buf[2+6*i]*4 + work_buf[3+6*i]*2 + work_buf[4+6*i];
			int sout = s_box[i][j][k];
			//[0+4i,3+4i]存放的是sout从右到左的二进制
			work_tmp[0+4*i]= (sout>>3)&1;
			work_tmp[1+4*i]= (sout>>2)&1;
			work_tmp[2+4*i]= (sout>>1)&1;
			work_tmp[3+4*i]= (sout>>0)&1;
		}

		//数据p转换:  Permute - P
		static UCHAR tb_p[32] = {	//permute p, 32->32
              16,7,20,21, 29,12,28,17, 1,15,23,26,
               5,18,31,10, 2,8,24,14, 32,27,3,9,
              19,13,30,6, 22,11,4,25
		};
		for (int i=0; i<32; i++)
			work_buf[i] = work_tmp[tb_p[i]-1];

		//到这一步，work_buf相当于存放的是函数E之后的值
		//数据异或处理: data_buf XOR work_buf, 
		//左右交换
		for (i = 0; i < 32; i++) 
		{
			j = data_buf[i+32];
			data_buf[i+32] = data_buf[i] ^ work_buf[i];
			data_buf[i] = j;
		}
	} /* End of Iter */
	
	
	//数据左右交换
	for (i = 0; i < 32; i++) 
	{
		j = data_buf[i];
		data_buf[i] = data_buf[32+i];
		data_buf[32+i] = j;
	}
	
	//数据最终IP转换: Inverse Initial Permutation
	static UCHAR tb_inv_ip[64] =	// Inverse Initial Permutation, 64->64
	{ 
       40,8,48,16,56,24,64,32, 39,7,47,15,55,23,63,31,
       38,6,46,14,54,22,62,30, 37,5,45,13,53,21,61,29,
       36,4,44,12,52,20,60,28, 35,3,43,11,51,19,59,27,
       34,2,42,10,50,18,58,26, 33,1,41,9,49,17,57,25
	};
	for (i=0; i<64; i++)
		data_tmp[i] = data_buf[tb_inv_ip[i]-1];


	//输出字符串，额，其实就是把它变成16进制而已
	for (i = 0; i < 8; i++) 
	{
		*(dest+i) = 0x00;
		for (k=0; k<8; k++)
			*(dest+i) = (*(dest+i))*2 + data_tmp[i*8+k];
	}
}


