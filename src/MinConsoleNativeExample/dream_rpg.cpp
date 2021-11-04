#include "..\MinConsoleNative\MinConsoleNative.h"
#include <vector>  //vector
#include <iomanip> //setprecision
#include <sstream> //stringstream
using namespace std;

#include "XRandom.h" //random support
using _Random = effolkronium::random_static;

//precision = 0
wstring Float2Wstring(float value)
{
    std::wstringstream stream;
    //如果小数部分超过0.01, 则显示1位小数
    float diff = value - (int)value;
    if (diff > 0.01f)
    {
        stream << std::fixed << std::setprecision(1) << value;
    }
    else
    {
        stream << std::fixed << std::setprecision(0) << value;
    }
    return stream.str();
}

//伤害类型
enum class DamageType
{
    AD = 1,
    AP = 2,
    True = 3,
};

//攻击类型
enum class AttackType
{
    Attack = 1,     //普通攻击
    Ability = 2,    //技能
};

class ItemBase;

class CharacterBase
{
public:
    wstring Name;                   //角色名字
    vector<ItemBase*> Items;        //装备列表

public:
    float Health;                   //生命
    float Mana;                     //魔法
    float HealthRegen;              //生命回复(每秒)
    float ManaRegen;                //魔法回复(每秒)

    float AttackDamage;             //攻击力
    float Armor;                    //护甲
    float AbilityPower;             //法强
    float MagicResist;              //魔抗

    float AttackSpeed;              //攻击速度
    float AbilityHaste;             //技能急速

    float CriticalStrikeChance;     //暴击率
    float CriticalStrikeDamage;     //暴击伤害(默认为200%, +50%则=250%)

    float ArmorPenetrationValue;    //护甲值穿透
    float MagicPenetrationValue;    //法术值穿透
    float ArmorPenetrationRate;     //护甲穿透(百分比)
    float MagicPenetrationRate;     //法术穿透(百分比)

    float LifeSteal;                //生命偷取(普通攻击吸血)
    float OmniVamp;                 //全能吸血(造成伤害后即可吸血)

public:
    CharacterBase(wstring name)
    {
        this->Name = name;
        this->Health = 0;
        this->Mana = 0;
        this->HealthRegen = 0;
        this->ManaRegen = 0;
        this->AttackDamage = 0;
        this->Armor = 0;
        this->AbilityPower = 0;
        this->MagicResist = 0;
        this->AttackSpeed = 0;
        this->AbilityHaste = 0;
        this->CriticalStrikeChance = 0;
        this->CriticalStrikeDamage = 0;
        this->ArmorPenetrationValue = 0;
        this->MagicPenetrationValue = 0;
        this->ArmorPenetrationRate = 0;
        this->MagicPenetrationRate = 0;
        this->LifeSteal = 0;
        this->OmniVamp = 0;
    }

    void AddItem(ItemBase& item);

    float GetHealth();

    float GetMana();

    float GetHealthRegen();

    float GetManaRegen();

    float GetAttackDamage();

    float GetArmor();

    float GetAbilityPower();

    float GetMagicResist();

    float GetAttackSpeed();

    float GetAbilityHaste();

    float GetCriticalStrikeChance();

    float GetCriticalStrikeDamage();

    float GetArmorPenetrationValue();

    float GetMagicPenetrationValue();

    float GetArmorPenetrationRate();

    float GetMagicPenetrationRate();

    float GetLifeSteal();

    float GetOmniVamp();

    void OnHit(const CharacterBase& other, DamageType damageType, AttackType attackType);
};

class ItemBase
{
public:
    wstring Name;                   //装备名字
    wstring Describe;               //装备描述
    wstring Passive;                //被动技能描述

    float Health;                   //生命
    float Mana;                     //魔法
    float HealthRegen;              //生命回复(每秒)
    float ManaRegen;                //魔法回复(每秒)

    float AttackDamage;             //攻击力
    float Armor;                    //护甲
    float AbilityPower;             //法强
    float MagicResist;              //魔抗

    float AttackSpeed;              //攻击速度
    float AbilityHaste;             //技能急速

    float CriticalStrikeChance;     //暴击率
    float CriticalStrikeDamage;     //暴击伤害(默认为200%, +50%则=250%)

    float ArmorPenetrationValue;    //护甲值穿透
    float MagicPenetrationValue;    //法术值穿透
    float ArmorPenetrationRate;     //护甲穿透(百分比)
    float MagicPenetrationRate;     //法术穿透(百分比)

    float LifeSteal;                //生命偷取(普通攻击吸血)
    float OmniVamp;                 //全能吸血(造成伤害后即可吸血)

    ItemBase()
    {
        this->Name = L"Item";
        this->Describe = L"";
        this->Passive = L"";
        this->Health = 0;
        this->Mana = 0;
        this->HealthRegen = 0;
        this->ManaRegen = 0;
        this->AttackDamage = 0;
        this->Armor = 0;
        this->AbilityPower = 0;
        this->MagicResist = 0;
        this->AttackSpeed = 0;
        this->AbilityHaste = 0;
        this->CriticalStrikeChance = 0;
        this->CriticalStrikeDamage = 0;
        this->ArmorPenetrationValue = 0;
        this->MagicPenetrationValue = 0;
        this->ArmorPenetrationRate = 0;
        this->MagicPenetrationRate = 0;
        this->LifeSteal = 0;
        this->OmniVamp = 0;
    }

    wstring GetInfo()
    {
        wstring info;
        info += this->Name;

        if (this->Health != 0)
        {
            info += (L" 生命值+" + Float2Wstring(this->Health));
        }
        if (this->Mana != 0)
        {
            info += (L" 魔法值+" + Float2Wstring(this->Mana));
        }
        if (this->HealthRegen != 0)
        {
            info += (L" 生命回复+" + Float2Wstring(this->HealthRegen));
        }
        if (this->ManaRegen != 0)
        {
            info += (L" 魔法回复+" + Float2Wstring(this->ManaRegen));
        }
        if (this->AttackDamage != 0)
        {
            info += (L" 攻击力+" + Float2Wstring(this->AttackDamage));
        }
        if (this->Armor != 0)
        {
            info += (L" 护甲+" + Float2Wstring(this->Armor));
        }
        if (this->AbilityPower != 0)
        {
            info += (L" 法术强度+" + Float2Wstring(this->AbilityPower));
        }
        if (this->MagicResist != 0)
        {
            info += (L" 魔抗+" + Float2Wstring(this->MagicResist));
        }
        if (this->AttackSpeed != 0)
        {
            info += (L" 攻击速度+" + Float2Wstring(this->AttackSpeed) + L"%");
        }
        if (this->AbilityHaste != 0)
        {
            info += (L" 技能急速+" + Float2Wstring(this->AbilityHaste));
        }
        if (this->CriticalStrikeChance != 0)
        {
            info += (L" 暴击率+" + Float2Wstring(this->CriticalStrikeChance) + L"%");
        }
        if (this->CriticalStrikeDamage != 0)
        {
            info += (L" 暴击伤害+" + Float2Wstring(this->CriticalStrikeDamage) + L"%");
        }
        if (this->ArmorPenetrationValue != 0)
        {
            info += (L" 护甲值穿透+" + Float2Wstring(this->ArmorPenetrationValue));
        }
        if (this->MagicPenetrationValue != 0)
        {
            info += (L" 法术值穿透+" + Float2Wstring(this->MagicPenetrationValue));
        }
        if (this->ArmorPenetrationRate != 0)
        {
            info += (L" 护甲穿透+" + Float2Wstring(this->ArmorPenetrationRate) + L"%");
        }
        if (this->MagicPenetrationRate != 0)
        {
            info += (L" 法术穿透+" + Float2Wstring(this->MagicPenetrationRate) + L"%");
        }
        if (this->LifeSteal != 0)
        {
            info += (L" 生命偷取+" + Float2Wstring(this->LifeSteal) + L"%");
        }
        if (this->OmniVamp != 0)
        {
            info += (L" 全能吸血+" + Float2Wstring(this->OmniVamp) + L"%");
        }

        if (this->Passive != L"")
        {
            info += (L" 被动效果:" + this->Passive);
        }

        if (this->Describe != L"")
        {
            info += (L" (" + this->Describe + L")");
        }
        return info;
    }
};

void CharacterBase::AddItem(ItemBase& item)
{
    this->Items.push_back(&item);
}

float CharacterBase::GetHealth()
{
    float sum = this->Health;
    for (const auto& item : Items)
    {
        sum += item->Health;
    }
    return sum;
}

float CharacterBase::GetMana()
{
    float sum = this->Mana;
    for (const auto& item : Items)
    {
        sum += item->Mana;
    }
    return sum;
}

float CharacterBase::GetHealthRegen()
{
    float sum = this->HealthRegen;
    for (const auto& item : Items)
    {
        sum += item->HealthRegen;
    }
    return sum;
}

float CharacterBase::GetManaRegen()
{
    float sum = this->ManaRegen;
    for (const auto& item : Items)
    {
        sum += item->ManaRegen;
    }
    return sum;
}

float CharacterBase::GetAttackDamage()
{
    float sum = this->AttackDamage;
    for (const auto& item : Items)
    {
        sum += item->AttackDamage;
    }
    return sum;
}

float CharacterBase::GetArmor()
{
    float sum = this->Armor;
    for (const auto& item : Items)
    {
        sum += item->Armor;
    }
    return sum;
}

float CharacterBase::GetAbilityPower()
{
    float sum = this->AbilityPower;
    for (const auto& item : Items)
    {
        sum += item->AbilityPower;
    }
    return sum;
}

float CharacterBase::GetMagicResist()
{
    float sum = this->MagicResist;
    for (const auto& item : Items)
    {
        sum += item->MagicResist;
    }
    return sum;
}

float CharacterBase::GetAttackSpeed()
{
    float sum = this->AttackSpeed;
    for (const auto& item : Items)
    {
        sum += item->AttackSpeed;
    }
    return sum;
}

float CharacterBase::GetAbilityHaste()
{
    float sum = this->AbilityHaste;
    for (const auto& item : Items)
    {
        sum += item->AbilityHaste;
    }
    return sum;
}

float CharacterBase::GetCriticalStrikeChance()
{
    float sum = this->CriticalStrikeChance;
    for (const auto& item : Items)
    {
        sum += item->CriticalStrikeChance;
    }
    return sum;
}

float CharacterBase::GetCriticalStrikeDamage()
{
    float sum = this->CriticalStrikeDamage;
    for (const auto& item : Items)
    {
        sum += item->CriticalStrikeDamage;
    }
    return sum;
}

float CharacterBase::GetArmorPenetrationValue()
{
    float sum = this->ArmorPenetrationValue;
    for (const auto& item : Items)
    {
        sum += item->ArmorPenetrationValue;
    }
    return sum;
}

float CharacterBase::GetMagicPenetrationValue()
{
    float sum = this->MagicPenetrationValue;
    for (const auto& item : Items)
    {
        sum += item->MagicPenetrationValue;
    }
    return sum;
}

float CharacterBase::GetArmorPenetrationRate()
{
    float sum = this->ArmorPenetrationRate;
    for (const auto& item : Items)
    {
        sum += item->ArmorPenetrationRate;
    }
    return sum;
}

float CharacterBase::GetMagicPenetrationRate()
{
    float sum = this->MagicPenetrationRate;
    for (const auto& item : Items)
    {
        sum += item->MagicPenetrationRate;
    }
    return sum;
}

float CharacterBase::GetLifeSteal()
{
    float sum = this->LifeSteal;
    for (const auto& item : Items)
    {
        sum += item->LifeSteal;
    }
    return sum;
}

float CharacterBase::GetOmniVamp()
{
    float sum = this->OmniVamp;
    for (const auto& item : Items)
    {
        sum += item->OmniVamp;
    }
    return sum;
}

void CharacterBase::OnHit(const CharacterBase& other, DamageType damageType, AttackType attackType)
{
    switch (attackType)
    {
    case AttackType::Attack:

        break;
    case AttackType::Ability:

        break;
    }

    switch (damageType)
    {
    case DamageType::AD:
        //bool criticalStrike = _Random::get<bool>();
        //other.CriticalStrikeChance;
        break;
    case DamageType::AP:
        break;
    case DamageType::True:
        break;
    }
}


class DreamRPG : public ConsoleEngine
{
public:
    void OnStart() override
    {
        console.WriteLine(L"欢迎来到造梦联盟");

        ItemBase blade;
        blade.Name = L"饮血剑";
        blade.AttackDamage = 80.5f;
        blade.LifeSteal = 20;
        blade.CriticalStrikeChance = 20;
        wstring info = blade.GetInfo();
        console.WriteLine(info);

        ItemBase monkeyBang;
        monkeyBang.Name = L"如意金箍棒";
        monkeyBang.AttackDamage = 125;
        monkeyBang.AttackSpeed = 20;
        monkeyBang.CriticalStrikeChance = 30;
        monkeyBang.Passive = L"暴击伤害+100%";
        monkeyBang.Describe = L"如意金箍棒, 重一万三千五百斤, 长叩三下, 鬼神俱至";
        wstring info2 = monkeyBang.GetInfo();
        console.WriteLine(info2);

        ItemBase battleArmor;
        battleArmor.Name = L"大圣战铠";
        battleArmor.Health = 1000;
        battleArmor.Armor = 50;
        battleArmor.Describe = L"攻无不克, 战无不胜";
        console.WriteLine(battleArmor.GetInfo());

        ItemBase evilRing;
        evilRing.Name = L"嗔恨邪戒";
        evilRing.AttackDamage = 40;
        evilRing.AbilityPower = 60;
        evilRing.ArmorPenetrationRate = 50;
        evilRing.MagicPenetrationRate = 50;
        evilRing.Describe = L"殿可毁, 人可亡, 恨犹在, 何时还?";
        console.WriteLine(evilRing.GetInfo());

        ItemBase gourd;
        gourd.Name = L"宣花葫芦";
        gourd.Health = 300;
        gourd.Mana = 300;
        gourd.Armor = 25;
        gourd.MagicResist = 25;
        gourd.Passive = L"攻击力+10%";
        gourd.Describe = L"街喧闹, 人过往, 且记曾相识, 不为少年留";
        console.WriteLine(gourd.GetInfo());

        console.WriteLine();

        CharacterBase monkey(L"悟空");
        monkey.Health = 60;
        monkey.AddItem(monkeyBang);
        monkey.AddItem(battleArmor);
        monkey.AddItem(battleArmor);
        console.WriteLine(monkey.Name + L"的生命值为:" + Float2Wstring(monkey.GetHealth()));
        console.WriteLine(monkey.Name + L"的攻击力为:" + Float2Wstring(monkey.GetAttackDamage()));
    }

    void OnUpdate(float deltaTime) override
    {

    }

    void OnDestroy() override
    {

    }
};

int main()
{
    DreamRPG game;

    game.ConstructTerminal(L"造梦联盟");
    game.StartLoop(60);

    return 0;
}