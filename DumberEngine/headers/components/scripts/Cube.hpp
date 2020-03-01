//
// Created by fab on 27/02/2020.
//

#ifndef DUMBERENGINE_CUBE_HPP
#define DUMBERENGINE_CUBE_HPP

class Cube
{
public :
    enum CubeType
    {
        CUBE_HERBE = 1,
        CUBE_TERRE,
        CUBE_BOIS,
        CUBE_PIERRE,
        CUBE_EAU,
        CUBE_VERRE,
        CUBE_PLANCHE_01,
        CUBE_PLANCHE_02,
        CUBE_PLANCHE_03,
        CUBE_PLANCHE_04,
        CUBE_PLANCHE_05,
        CUBE_PLANCHE_06,
        CUBE_BRIQUES,
        CUBE_DALLES_01,
        CUBE_DALLES_02,
        CUBE_DALLES_03,
        CUBE_DALLES_04,
        CUBE_SABLE_01,
        CUBE_SABLE_02,
        CUBE_LAINE_01,
        CUBE_LAINE_02,
        CUBE_LAINE_03,
        CUBE_LAINE_04,
        CUBE_LAINE_05,
        CUBE_LAINE_06,
        CUBE_LAINE_07,
        CUBE_LAINE_08,
        CUBE_LAINE_09,
        CUBE_LAINE_10,
        CUBE_LAINE_11,
        CUBE_LAINE_12,
        CUBE_LAINE_13,
        CUBE_LAINE_14,
        CUBE_LAINE_15,
        CUBE_LAINE_16,

        CUBE_CUSTOM_IMAGE,
        CUBE_LIVRE,

        CUBE_TRONC,
        CUBE_BRANCHES,
        CUBE_AIR,

        CUBE_STAIRS,
        CUBE_NB_TYPES
    }; //Limité à 128 types

    static const int CUBE_DRAW_BIT = 0x80;

public :
    unsigned char _Code; // only the first part is used, the second part is the flag

public :
    static const int CUBE_SIZE = 1;

    Cube()
    {
        setDraw(false);
        setType(CUBE_AIR);
    }

    void setType(CubeType type)
    {
        bool draw = getDraw();
        _Code = (unsigned char) type;
        setDraw(draw);
    }

    CubeType getType()
    {
        return (CubeType) (_Code & ~CUBE_DRAW_BIT);
    }

    bool getDraw()
    {
        return (_Code & CUBE_DRAW_BIT) != 0;
    }

    void setDraw(bool draw)
    {
        if (draw)
            _Code |= CUBE_DRAW_BIT;
        else
            _Code &= ~CUBE_DRAW_BIT;
    }

    bool isSolid()
    {
        CubeType type = getType();
        return (type != CUBE_AIR && type != CUBE_EAU);
    }

    bool isPickable()
    {
        CubeType type = getType();
        return (type != CUBE_AIR);
    }

    bool isOpaque()
    {
        CubeType type = getType();
        return (type != CUBE_AIR && type != CUBE_EAU && type != CUBE_VERRE && type != CUBE_BRANCHES);
    }

    bool isTransparent(void)
    {
        CubeType type = getType();
        return (type == CUBE_AIR || type == CUBE_EAU || type == CUBE_VERRE);
    }

    bool isCutoff(void)
    {
        CubeType type = getType();
        return (type == CUBE_BRANCHES);
    }

    bool isGround(void)
    {
        CubeType type = getType();
        return (type == CUBE_HERBE || type == CUBE_TERRE || type == CUBE_EAU || type == CUBE_BOIS ||
                type == CUBE_PIERRE);
    }

    unsigned char getRawCode()
    {
        return _Code;
    }

    void setRawCode(unsigned char code)
    {
        _Code = code;
    }

    static bool isManipulable(CubeType type)
    {
        switch (type)
        {
            case CUBE_HERBE:
            case CUBE_TERRE:
            case CUBE_BOIS:
            case CUBE_PIERRE:
            case CUBE_EAU:
            case CUBE_VERRE:
            case CUBE_STAIRS:
            case CUBE_PLANCHE_01:
            case CUBE_PLANCHE_02:
            case CUBE_PLANCHE_03:
            case CUBE_PLANCHE_04:
            case CUBE_PLANCHE_05:
            case CUBE_PLANCHE_06:
            case CUBE_BRIQUES:
            case CUBE_DALLES_01:
            case CUBE_DALLES_02:
            case CUBE_DALLES_03:
            case CUBE_DALLES_04:
            case CUBE_SABLE_01:
            case CUBE_SABLE_02:
            case CUBE_LAINE_01:
            case CUBE_LAINE_02:
            case CUBE_LAINE_03:
            case CUBE_LAINE_04:
            case CUBE_LAINE_05:
            case CUBE_LAINE_06:
            case CUBE_LAINE_07:
            case CUBE_LAINE_08:
            case CUBE_LAINE_09:
            case CUBE_LAINE_10:
            case CUBE_LAINE_11:
            case CUBE_LAINE_12:
            case CUBE_LAINE_13:
            case CUBE_LAINE_14:
            case CUBE_LAINE_15:
            case CUBE_LAINE_16:
            case CUBE_CUSTOM_IMAGE:
            case CUBE_LIVRE:
            case CUBE_TRONC:
                return true;
        }

        return false;
    }
};

#endif //DUMBERENGINE_CUBE_HPP
