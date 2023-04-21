#include <Novice.h>
#include <math.h>
const char kWindowTitle[] = "LE2B_14_サカキバラ_イブキ";
#include<Default.h>
#include <cassert>
//余因子行列

static const int kRowHeight = 20;
static const int kColumnWidth = 60;

static const int rMax = 4;
static const int cMax = 4;
void MatrixScreenPrint(int x, int y, const Matrix4x4& matrix,const char* label)
{
	Novice::ScreenPrintf(x, y, "%s", label);
	y += kRowHeight;
	for (int row = 0; row < rMax; ++row)
	{
		for (int column = 0; column < cMax; ++column)
		{
			Novice::ScreenPrintf(
				x + column * kColumnWidth,
				y + row * kRowHeight,
				"%6.02f", matrix.m[row][column]
			);
		}
	}


}

Matrix4x4 Add(const Matrix4x4& m1, const Matrix4x4& m2)
{
	Matrix4x4 result;

	for (int r = 0; r < rMax; r++)
	{
		for (int c = 0; c < cMax; c++)
		{
			result.m[r][c] = m1.m[r][c] + m2.m[r][c];

		}

	}

	return result;
}
Matrix4x4 Subract(const Matrix4x4& m1, const Matrix4x4& m2)
{
	Matrix4x4 result;
	for (int r = 0; r < rMax; r++)
	{
		for (int c = 0; c < cMax; c++)
		{
			result.m[r][c] = m1.m[r][c] - m2.m[r][c];
		}

	}

	return result;
}

Matrix4x4 Multiply(const Matrix4x4& m1, const Matrix4x4& m2)
{
	Matrix4x4 result;
	
	for (int r = 0; r < rMax; r++)
	{
		for (int c = 0; c < cMax; c++)
		{
			float tmp=0.0f;
			for (int i = 0; i < 4; i++)
			{
				tmp = tmp + m1.m[r][i] * m2.m[i][c];
				result.m[r][c] = tmp;
			}
		}

	}
	return result;
}

Matrix4x4 Inverse(const Matrix4x4 &matrix)
{
	Matrix4x4 result;
	float determinant =
		matrix.m[0][0] * matrix.m[1][1] * matrix.m[2][2] * matrix.m[3][3] +
		matrix.m[0][0] * matrix.m[1][2] * matrix.m[2][3] * matrix.m[3][1] +
		matrix.m[0][0] * matrix.m[1][3] * matrix.m[2][1] * matrix.m[3][2] -

		matrix.m[0][0] * matrix.m[1][3] * matrix.m[2][2] * matrix.m[3][1] -
		matrix.m[0][0] * matrix.m[1][2] * matrix.m[2][1] * matrix.m[3][3] -
		matrix.m[0][0] * matrix.m[1][1] * matrix.m[2][3] * matrix.m[3][2] -

		matrix.m[0][1] * matrix.m[1][0] * matrix.m[2][2] * matrix.m[3][3] -
		matrix.m[0][2] * matrix.m[1][0] * matrix.m[2][3] * matrix.m[3][1] -
		matrix.m[0][3] * matrix.m[1][0] * matrix.m[2][1] * matrix.m[3][2] +

		matrix.m[0][3] * matrix.m[1][0] * matrix.m[2][2] * matrix.m[3][1] +
		matrix.m[0][2] * matrix.m[1][0] * matrix.m[2][1] * matrix.m[3][3] +
		matrix.m[0][1] * matrix.m[1][0] * matrix.m[2][3] * matrix.m[3][2] +

		matrix.m[0][1] * matrix.m[1][2] * matrix.m[2][0] * matrix.m[3][3] +
		matrix.m[0][2] * matrix.m[1][3] * matrix.m[2][0] * matrix.m[3][1] +
		matrix.m[0][3] * matrix.m[1][1] * matrix.m[2][0] * matrix.m[3][2] -

		matrix.m[0][3] * matrix.m[1][2] * matrix.m[2][0] * matrix.m[3][1] -
		matrix.m[0][2] * matrix.m[1][1] * matrix.m[2][0] * matrix.m[3][3] -
		matrix.m[0][1] * matrix.m[1][3] * matrix.m[2][0] * matrix.m[3][2] -

		matrix.m[0][1] * matrix.m[1][2] * matrix.m[2][3] * matrix.m[3][0] -
		matrix.m[0][2] * matrix.m[1][3] * matrix.m[2][1] * matrix.m[3][0] -
		matrix.m[0][3] * matrix.m[1][1] * matrix.m[2][2] * matrix.m[3][0] +

		matrix.m[0][3] * matrix.m[1][2] * matrix.m[2][1] * matrix.m[3][0] +
		matrix.m[0][2] * matrix.m[1][1] * matrix.m[2][3] * matrix.m[3][0] +
		matrix.m[0][1] * matrix.m[1][3] * matrix.m[2][2] * matrix.m[3][0];

	assert(determinant != 0.0f);
	float determinantRecp = 1.0f / determinant;

	result.m[0][0] =
		(
			matrix.m[1][1] * matrix.m[2][2] * matrix.m[3][3] +
			matrix.m[1][2] * matrix.m[2][3] * matrix.m[3][1] +
			matrix.m[1][3] * matrix.m[2][1] * matrix.m[3][2] -
			matrix.m[1][3] * matrix.m[2][2] * matrix.m[3][1] -
			matrix.m[1][2] * matrix.m[2][1] * matrix.m[3][3] -
			matrix.m[1][1] * matrix.m[2][3] * matrix.m[3][2]

			) * determinantRecp;






	return result;
}


// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, 1280, 720);

	// キー入力結果を受け取る箱
	char keys[256] = {0};
	char preKeys[256] = {0};


	Matrix4x4 m1 =
	{
		3.2f,0.7f,9.6f,4.4f,
		5.5f,1.3f,7.8f,2.1f,
		6.9f,8.0f,2.6f,1.0f,
		0.5f,7.2f,5.1f,3.3f
	};
	Matrix4x4 m2 =
	{
		4.1f,6.5f,3.3f,2.2f,
		8.8f,0.6f,9.9f,7.7f,
		1.1f,5.5f,6.6f,0.0f,
		3.3f,9.9f,8.8f,2.2f
	};

	Matrix4x4 resultAdd = Add(m1, m2);
	Matrix4x4 resultSubtract = Subract(m1, m2);
	Matrix4x4 resultMultiply = Multiply(m1, m2);
	Matrix4x4 resultInverseM1 = Inverse(m1);
	// ウィンドウの×ボタンが押されるまでループ
	while (Novice::ProcessMessage() == 0) {
		// フレームの開始
		Novice::BeginFrame();

		// キー入力を受け取る
		memcpy(preKeys, keys, 256);
		Novice::GetHitKeyStateAll(keys);

		///
		/// ↓更新処理ここから
		///

		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///
		MatrixScreenPrint(0, 0, resultAdd,"Add");
		MatrixScreenPrint(0, kRowHeight*5, resultSubtract, "Subtract");
		MatrixScreenPrint(0, kRowHeight * 5 * 2, resultMultiply, "Multiply");
		MatrixScreenPrint(0, kRowHeight * 5 * 3, resultInverseM1, "inverseM1");
		///
		/// ↑描画処理ここまで
		///

		// フレームの終了
		Novice::EndFrame();

		// ESCキーが押されたらループを抜ける
		if (preKeys[DIK_ESCAPE] == 0 && keys[DIK_ESCAPE] != 0) {
			break;
		}
	}

	// ライブラリの終了
	Novice::Finalize();
	return 0;
}
