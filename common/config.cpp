#include "config.h"
#include "define.h"
#include "../sdk/sdk.h"
#include "toolbar.h"
#include "label.h"

bool CConfig::label_mix_comment()
{
    return false;
}

#define ENABLE_JMP TEXT("enable_jmp")

void CConfig::loadall()
{
    // label��س�ʼ��
    width_label = get_int(WIDTH_LABEL, DEFAULT_WIDTH_LABEL);
    width_comment = get_int(WIDTH_COMMENT, DEFAULT_WIDTH_COMMENT);
    label_enabled_ = get_int(LABEL_ENABLE, 1);

#ifdef HOLYSHIT_EXPORTS
    enable_jmp = get_int(ENABLE_JMP, 0);
#else
    enable_jmp = get_int(ENABLE_JMP, 1);
#endif

    //if (!label_enabled_)
    //{
    //    check_.push_back(NM_COMMENT);
    //}
    check_.push_back(NM_LABEL);
    check_.push_back(NM_EXPORT);

    TCHAR szTB[MAX_PATH];
    CConfig_Single.get_str(INI_PATH, szTB, TEXT(""));
    ini_path = TEXT("");
    ini_path = szTB;
}

void CConfig::saveall(bool now)
{
    if (label_enabled())
    {
        if (now)
        {
            width_label = get_width_label_now();
            width_comment = get_width_comment_now();
        }

        if(width_label && width_comment)
        {
            set_int(WIDTH_LABEL, width_label);
            set_int(WIDTH_COMMENT, width_comment);
        }
    }
    set_int(LABEL_ENABLE, label_enabled_);
    set_int(ENABLE_JMP, enable_jmp);
    set_str(INI_PATH, (LPTSTR)ini_path.c_str());
}


int CConfig::get_int( TCHAR* key, int def )
{
#ifdef HOLYSHIT_EXPORTS
    return Pluginreadintfromini(plugin_mod, key, def);
#else
    int ret = def;
    Getfromini(NULL, PLUGIN_NAME, key, L"%i", &ret);
    return ret;
#endif
}

int CConfig::set_int( TCHAR* key, int value )
{
#ifdef HOLYSHIT_EXPORTS
    return Pluginwriteinttoini(plugin_mod, key, value);
#else
    return Writetoini(NULL, PLUGIN_NAME, key, L"%i", value);
#endif
}

int CConfig::get_str( TCHAR* key, LPTSTR str_buf, LPTSTR def )
{
#ifdef HOLYSHIT_EXPORTS
    return Pluginreadstringfromini(plugin_mod, key, str_buf, def);
#else
    return Getfromini(NULL, PLUGIN_NAME, key, L"%s", str_buf);
#endif
}

int CConfig::set_str( TCHAR* key, LPTSTR str )
{
#ifdef HOLYSHIT_EXPORTS
    return Pluginwritestringtoini(plugin_mod, key, str);
#else
    return Writetoini(NULL, PLUGIN_NAME, key, L"%s", str);
#endif
}

CConfig& CConfig::getInstance()
{

    static CConfig b;
    return b;
}

void CConfig::set_mod( HMODULE mod )
{plugin_mod = mod;}

bool CConfig::label_enabled(){return label_enabled_;}

const std::vector<int>& CConfig::check() const
{return check_;}

int CConfig::get_width_label()
{return width_label;}

int CConfig::get_width_comment()
{return width_comment;}

void CConfig::set_width_label( int i )
{width_label = i;}

void CConfig::set_width_comment( int i )
{width_comment = i;}

std::tstring CConfig::get_ini_path()
{return ini_path;}

void CConfig::set_ini_path( const std::tstring& path )
{ ini_path = path;}



