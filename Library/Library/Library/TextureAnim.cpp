#include "TextureAnim.h"
#include "AnimFileParser.h"

Lib::TextureAnim::TextureAnim()
{
	m_pAnimFileParser = new AnimFileParser();
}

Lib::TextureAnim::~TextureAnim()
{
	delete m_pAnimFileParser;
}

void Lib::TextureAnim::LoadAnimation(LPCTSTR _pFileName,LPCTSTR _pAnimName)
{
	m_pAnimFileParser->FileLoad(_pFileName);
	std::vector<float> Data;
	m_pAnimFileParser->ReadData(_pAnimName, &Data);
	m_AnimData.Width;

}
