#include <DxLib.h>
#include "Application.h"

// WinMain�֐�
//---------------------------------
int WINAPI WinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nCmdShow)
{

	// �C���X�^���X�̐���
	Application application;

	// ��������
	application.Init();
	if (application.IsError())
	{
		return -1;
	}

	// �Q�[�����[�v�N��
	application.Run();

	// �������
	application.Release();
	if (application.IsError())
	{
		return -1;
	}

	return 0;

}