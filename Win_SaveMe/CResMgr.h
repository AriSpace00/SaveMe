#pragma once

class CTexture;
class CSound;

class CResMgr
{
    SINGLE(CResMgr);

private:
    // ��� �ؽ�ó�� ���ҽ� �Ŵ������� ������ ���̴�.
    // �ؽ�ó�� string Ű ������ ã�Ƽ� ����� �� �ִ�.
    map<wstring, CTexture*> m_mapTex;

public:
    // Ű ������ �ؽ�ó ã��, ��� ���󰡼� �ε�
    CTexture* LoadTexture(const wstring& _strKey, const wstring& _strRelativePath);
    // Ű ������ �ߺ��� �ؽ�ó ã��
    CTexture* FindTexture(const wstring& _strKey);

    CSound* LoadSound(const wstring& _strPath);

};

