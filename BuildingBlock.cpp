#include "BuildingBlock.h"

static void printfCommentSquare(FILE *fp, const std::string &content, int indent = 10)
{
    XASSERT(fp);

    int len = content.size();
    int cmtLen = len + indent * 2;

    for (int i = 0; i < cmtLen; ++i)
        std::fputs("/", fp);
    std::fputc('\n', fp);
    for (int i = 0; i < cmtLen; ++i)
        std::fputs("/", fp);
    std::fputc('\n', fp);

    std::fputs("//\n//", fp);
    for (int i = 2; i < indent; ++i)
        std::fputc(' ', fp);
    std::fprintf(fp, "%s\n", content.c_str());
    std::fputs("//\n", fp);

    for (int i = 0; i < cmtLen; ++i)
        std::fputs("/", fp);
    std::fputc('\n', fp);
    for (int i = 0; i < cmtLen; ++i)
        std::fputs("/", fp);
    std::fputc('\n', fp);
}

static const char *GetManagerGuidName(CKGUID guid)
{
    if (guid == OBJECT_MANAGER_GUID)
        return "OBJECT_MANAGER_GUID";
    if (guid == ATTRIBUTE_MANAGER_GUID)
        return "ATTRIBUTE_MANAGER_GUID";
    if (guid == MESSAGE_MANAGER_GUID)
        return "MESSAGE_MANAGER_GUID";
    if (guid == TIME_MANAGER_GUID)
        return "TIME_MANAGER_GUID";
    if (guid == SOUND_MANAGER_GUID)
        return "SOUND_MANAGER_GUID";
    if (guid == MIDI_MANAGER_GUID)
        return "MIDI_MANAGER_GUID";
    if (guid == INPUT_MANAGER_GUID)
        return "INPUT_MANAGER_GUID";
    if (guid == BEHAVIOR_MANAGER_GUID)
        return "BEHAVIOR_MANAGER_GUID";
    if (guid == FLOOR_MANAGER_GUID)
        return "FLOOR_MANAGER_GUID";
    if (guid == COLLISION_MANAGER_GUID)
        return "COLLISION_MANAGER_GUID";
    if (guid == GRID_MANAGER_GUID)
        return "GRID_MANAGER_GUID";
    if (guid == INTERFACE_MANAGER_GUID)
        return "INTERFACE_MANAGER_GUID";
    if (guid == RENDER_MANAGER_GUID)
        return "RENDER_MANAGER_GUID";
    if (guid == PARAMETER_MANAGER_GUID)
        return "PARAMETER_MANAGER_GUID";
    if (guid == PATH_MANAGER_GUID)
        return "PATH_MANAGER_GUID";
    else
    {
        static char buf[512];
        std::sprintf(buf, "CKGUID(%#lx,%#lx)", guid.d1, guid.d2);
        return buf;
    }
}

static const char *GetClassIdentifierName(CK_CLASSID cid)
{
    switch (cid)
    {
    case CKCID_OBJECT:
        return "CKCID_OBJECT";
    case CKCID_PARAMETERIN:
        return "CKCID_PARAMETERIN";
    case CKCID_PARAMETEROPERATION:
        return "CKCID_PARAMETEROPERATION";
    case CKCID_STATE:
        return "CKCID_STATE";
    case CKCID_BEHAVIORLINK:
        return "CKCID_BEHAVIORLINK";
    case CKCID_BEHAVIOR:
        return "CKCID_BEHAVIOR";
    case CKCID_BEHAVIORIO:
        return "CKCID_BEHAVIORIO";
    case CKCID_RENDERCONTEXT:
        return "CKCID_RENDERCONTEXT";
    case CKCID_KINEMATICCHAIN:
        return "CKCID_KINEMATICCHAIN";
    case CKCID_SCENEOBJECT:
        return "CKCID_SCENEOBJECT";
    case CKCID_OBJECTANIMATION:
        return "CKCID_OBJECTANIMATION";
    case CKCID_ANIMATION:
        return "CKCID_ANIMATION";
    case CKCID_KEYEDANIMATION:
        return "CKCID_KEYEDANIMATION";
    case CKCID_BEOBJECT:
        return "CKCID_BEOBJECT";
    case CKCID_DATAARRAY:
        return "CKCID_DATAARRAY";
    case CKCID_SCENE:
        return "CKCID_SCENE";
    case CKCID_LEVEL:
        return "CKCID_LEVEL";
    case CKCID_PLACE:
        return "CKCID_PLACE";
    case CKCID_GROUP:
        return "CKCID_GROUP";
    case CKCID_SOUND:
        return "CKCID_SOUND";
    case CKCID_WAVESOUND:
        return "CKCID_WAVESOUND";
    case CKCID_MIDISOUND:
        return "CKCID_MIDISOUND";
    case CKCID_MATERIAL:
        return "CKCID_MATERIAL";
    case CKCID_TEXTURE:
        return "CKCID_TEXTURE";
    case CKCID_MESH:
        return "CKCID_MESH";
    case CKCID_PATCHMESH:
        return "CKCID_PATCHMESH";
    case CKCID_RENDEROBJECT:
        return "CKCID_RENDEROBJECT";
    case CKCID_2DENTITY:
        return "CKCID_2DENTITY";
    case CKCID_SPRITE:
        return "CKCID_SPRITE";
    case CKCID_SPRITETEXT:
        return "CKCID_SPRITETEXT";
    case CKCID_3DENTITY:
        return "CKCID_3DENTITY";
    case CKCID_GRID:
        return "CKCID_GRID";
    case CKCID_CURVEPOINT:
        return "CKCID_CURVEPOINT";
    case CKCID_SPRITE3D:
        return "CKCID_SPRITE3D";
    case CKCID_CURVE:
        return "CKCID_CURVE";
    case CKCID_CAMERA:
        return "CKCID_CAMERA";
    case CKCID_TARGETCAMERA:
        return "CKCID_TARGETCAMERA";
    case CKCID_LIGHT:
        return "CKCID_LIGHT";
    case CKCID_TARGETLIGHT:
        return "CKCID_TARGETLIGHT";
    case CKCID_CHARACTER:
        return "CKCID_CHARACTER";
    case CKCID_3DOBJECT:
        return "CKCID_3DOBJECT";
    case CKCID_BODYPART:
        return "CKCID_BODYPART";
    case CKCID_PARAMETER:
        return "CKCID_PARAMETER";
    case CKCID_PARAMETERLOCAL:
        return "CKCID_PARAMETERLOCAL";
    case CKCID_PARAMETERVARIABLE:
        return "CKCID_PARAMETERVARIABLE";
    case CKCID_PARAMETEROUT:
        return "CKCID_PARAMETEROUT";
    case CKCID_INTERFACEOBJECTMANAGER:
        return "CKCID_INTERFACEOBJECTMANAGER";
    case CKCID_CRITICALSECTION:
        return "CKCID_CRITICALSECTION";
    case CKCID_LAYER:
        return "CKCID_LAYER";
    case CKCID_PROGRESSIVEMESH:
        return "CKCID_PROGRESSIVEMESH";
    case CKCID_MAXCLASSID:
        return "CKCID_MAXCLASSID";
    case CKCID_SYNCHRO:
        return "CKCID_SYNCHRO";
    default:
    {
        static char buf[512];
        std::sprintf(buf, "%ld", cid);
        return buf;
    }
    }
}

static const char *GetPreregisteredParameterTypeName(CKGUID guid)
{
    if (guid == CKPGUID_NONE)
        return "CKPGUID_NONE";
    else if (guid == CKPGUID_VOIDBUF)
        return "CKPGUID_VOIDBUF";
    else if (guid == CKPGUID_FLOAT)
        return "CKPGUID_FLOAT";
    else if (guid == CKPGUID_ANGLE)
        return "CKPGUID_ANGLE";
    else if (guid == CKPGUID_PERCENTAGE)
        return "CKPGUID_PERCENTAGE";
    else if (guid == CKPGUID_INT)
        return "CKPGUID_INT";
    else if (guid == CKPGUID_KEY)
        return "CKPGUID_KEY";
    else if (guid == CKPGUID_BOOL)
        return "CKPGUID_BOOL";
    else if (guid == CKPGUID_STRING)
        return "CKPGUID_STRING";
    else if (guid == CKPGUID_RECT)
        return "CKPGUID_RECT";
    else if (guid == CKPGUID_VECTOR)
        return "CKPGUID_VECTOR";
    else if (guid == CKPGUID_2DVECTOR)
        return "CKPGUID_2DVECTOR";
    else if (guid == CKPGUID_QUATERNION)
        return "CKPGUID_QUATERNION";
    else if (guid == CKPGUID_EULERANGLES)
        return "CKPGUID_EULERANGLES";
    else if (guid == CKPGUID_MATRIX)
        return "CKPGUID_MATRIX";
    else if (guid == CKPGUID_COLOR)
        return "CKPGUID_COLOR";
    else if (guid == CKPGUID_BOX)
        return "CKPGUID_BOX";
    else if (guid == CKPGUID_OBJECTARRAY)
        return "CKPGUID_OBJECTARRAY";
    else if (guid == CKPGUID_OBJECT)
        return "CKPGUID_OBJECT";
    else if (guid == CKPGUID_BEOBJECT)
        return "CKPGUID_BEOBJECT";
    else if (guid == CKPGUID_MESH)
        return "CKPGUID_MESH";
    else if (guid == CKPGUID_MATERIAL)
        return "CKPGUID_MATERIAL";
    else if (guid == CKPGUID_TEXTURE)
        return "CKPGUID_TEXTURE";
    else if (guid == CKPGUID_SPRITE)
        return "CKPGUID_SPRITE";
    else if (guid == CKPGUID_3DENTITY)
        return "CKPGUID_3DENTITY";
    else if (guid == CKPGUID_CURVEPOINT)
        return "CKPGUID_CURVEPOINT";
    else if (guid == CKPGUID_LIGHT)
        return "CKPGUID_LIGHT";
    else if (guid == CKPGUID_TARGETLIGHT)
        return "CKPGUID_TARGETLIGHT";
    else if (guid == CKPGUID_ID)
        return "CKPGUID_ID";
    else if (guid == CKPGUID_CAMERA)
        return "CKPGUID_CAMERA";
    else if (guid == CKPGUID_TARGETCAMERA)
        return "CKPGUID_TARGETCAMERA";
    else if (guid == CKPGUID_SPRITE3D)
        return "CKPGUID_SPRITE3D";
    else if (guid == CKPGUID_OBJECT3D)
        return "CKPGUID_OBJECT3D";
    else if (guid == CKPGUID_BODYPART)
        return "CKPGUID_BODYPART";
    else if (guid == CKPGUID_CHARACTER)
        return "CKPGUID_CHARACTER";
    else if (guid == CKPGUID_CURVE)
        return "CKPGUID_CURVE";
    else if (guid == CKPGUID_2DCURVE)
        return "CKPGUID_2DCURVE";
    else if (guid == CKPGUID_LEVEL)
        return "CKPGUID_LEVEL";
    else if (guid == CKPGUID_PLACE)
        return "CKPGUID_PLACE";
    else if (guid == CKPGUID_GROUP)
        return "CKPGUID_GROUP";
    else if (guid == CKPGUID_2DENTITY)
        return "CKPGUID_2DENTITY";
    else if (guid == CKPGUID_RENDEROBJECT)
        return "CKPGUID_RENDEROBJECT";
    else if (guid == CKPGUID_SPRITETEXT)
        return "CKPGUID_SPRITETEXT";
    else if (guid == CKPGUID_SOUND)
        return "CKPGUID_SOUND";
    else if (guid == CKPGUID_WAVESOUND)
        return "CKPGUID_WAVESOUND";
    else if (guid == CKPGUID_MIDISOUND)
        return "CKPGUID_MIDISOUND";
    else if (guid == CKPGUID_OBJECTANIMATION)
        return "CKPGUID_OBJECTANIMATION";
    else if (guid == CKPGUID_ANIMATION)
        return "CKPGUID_ANIMATION";
    else if (guid == CKPGUID_KINEMATICCHAIN)
        return "CKPGUID_KINEMATICCHAIN";
    else if (guid == CKPGUID_SCENE)
        return "CKPGUID_SCENE";
    else if (guid == CKPGUID_BEHAVIOR)
        return "CKPGUID_BEHAVIOR";
    else if (guid == CKPGUID_MESSAGE)
        return "CKPGUID_MESSAGE";
    else if (guid == CKPGUID_SYNCHRO)
        return "CKPGUID_SYNCHRO";
    else if (guid == CKPGUID_CRITICALSECTION)
        return "CKPGUID_CRITICALSECTION";
    else if (guid == CKPGUID_STATE)
        return "CKPGUID_STATE";
    else if (guid == CKPGUID_ATTRIBUTE)
        return "CKPGUID_ATTRIBUTE";
    else if (guid == CKPGUID_CLASSID)
        return "CKPGUID_CLASSID";
    else if (guid == CKPGUID_DIRECTION)
        return "CKPGUID_DIRECTION";
    else if (guid == CKPGUID_BLENDMODE)
        return "CKPGUID_BLENDMODE";
    else if (guid == CKPGUID_FILTERMODE)
        return "CKPGUID_FILTERMODE";
    else if (guid == CKPGUID_BLENDFACTOR)
        return "CKPGUID_BLENDFACTOR";
    else if (guid == CKPGUID_FILLMODE)
        return "CKPGUID_FILLMODE";
    else if (guid == CKPGUID_LITMODE)
        return "CKPGUID_LITMODE";
    else if (guid == CKPGUID_SHADEMODE)
        return "CKPGUID_SHADEMODE";
    else if (guid == CKPGUID_GLOBALEXMODE)
        return "CKPGUID_GLOBALEXMODE";
    else if (guid == CKPGUID_ZFUNC)
        return "CKPGUID_ZFUNC";
    else if (guid == CKPGUID_ADDRESSMODE)
        return "CKPGUID_ADDRESSMODE";
    else if (guid == CKPGUID_WRAPMODE)
        return "CKPGUID_WRAPMODE";
    else if (guid == CKPGUID_3DSPRITEMODE)
        return "CKPGUID_3DSPRITEMODE";
    else if (guid == CKPGUID_FOGMODE)
        return "CKPGUID_FOGMODE";
    else if (guid == CKPGUID_LIGHTTYPE)
        return "CKPGUID_LIGHTTYPE";
    else if (guid == CKPGUID_SPRITEALIGN)
        return "CKPGUID_SPRITEALIGN";
    else if (guid == CKPGUID_SCRIPT)
        return "CKPGUID_SCRIPT";
    else if (guid == CKPGUID_LAYERTYPE)
        return "CKPGUID_LAYERTYPE";
    else if (guid == CKPGUID_STATECHUNK)
        return "CKPGUID_STATECHUNK";
    else if (guid == CKPGUID_DATAARRAY)
        return "CKPGUID_DATAARRAY";
    else if (guid == CKPGUID_COMPOPERATOR)
        return "CKPGUID_COMPOPERATOR";
    else if (guid == CKPGUID_BINARYOPERATOR)
        return "CKPGUID_BINARYOPERATOR";
    else if (guid == CKPGUID_SETOPERATOR)
        return "CKPGUID_SETOPERATOR";
    else if (guid == CKPGUID_SPRITETEXTALIGNMENT)
        return "CKPGUID_SPRITETEXTALIGNMENT";
    else if (guid == CKPGUID_OBSTACLEPRECISION)
        return "CKPGUID_OBSTACLEPRECISION";
    else if (guid == CKPGUID_OBSTACLEPRECISIONBEH)
        return "CKPGUID_OBSTACLEPRECISIONBEH";
    else if (guid == CKPGUID_OBSTACLE)
        return "CKPGUID_OBSTACLE";
    else if (guid == CKPGUID_PATCHMESH)
        return "CKPGUID_PATCHMESH";
    else if (guid == CKPGUID_POINTER)
        return "CKPGUID_POINTER";
    else if (guid == CKPGUID_ENUMS)
        return "CKPGUID_ENUMS";
    else if (guid == CKPGUID_STRUCTS)
        return "CKPGUID_STRUCTS";
    else if (guid == CKPGUID_FLAGS)
        return "CKPGUID_FLAGS";
    else if (guid == CKPGUID_FILTER)
        return "CKPGUID_FILTER";
    else if (guid == CKPGUID_TIME)
        return "CKPGUID_TIME";
    else if (guid == CKPGUID_OLDTIME)
        return "CKPGUID_OLDTIME";
    else if (guid == CKPGUID_COPYDEPENDENCIES)
        return "CKPGUID_COPYDEPENDENCIES";
    else if (guid == CKPGUID_DELETEDEPENDENCIES)
        return "CKPGUID_DELETEDEPENDENCIES";
    else if (guid == CKPGUID_SAVEDEPENDENCIES)
        return "CKPGUID_SAVEDEPENDENCIES";
    else if (guid == CKPGUID_REPLACEDEPENDENCIES)
        return "CKPGUID_REPLACEDEPENDENCIES";
    else if (guid == CKPGUID_SCENEACTIVITYFLAGS)
        return "CKPGUID_SCENEACTIVITYFLAGS";
    else if (guid == CKPGUID_SCENEOBJECT)
        return "CKPGUID_SCENEOBJECT";
    else if (guid == CKPGUID_SCENERESETFLAGS)
        return "CKPGUID_SCENERESETFLAGS";
    else if (guid == CKPGUID_ARRAYTYPE)
        return "CKPGUID_ARRAYTYPE";
    else if (guid == CKPGUID_RENDEROPTIONS)
        return "CKPGUID_RENDEROPTIONS";
    else if (guid == CKPGUID_PARAMETERTYPE)
        return "CKPGUID_PARAMETERTYPE";
    else if (guid == CKPGUID_MATERIALEFFECT)
        return "CKPGUID_MATERIALEFFECT";
    else if (guid == CKPGUID_TEXGENEFFECT)
        return "CKPGUID_TEXGENEFFECT";
    else if (guid == CKPGUID_TEXGENREFEFFECT)
        return "CKPGUID_TEXGENREFEFFECT";
    else if (guid == CKPGUID_COMBINE2TEX)
        return "CKPGUID_COMBINE2TEX";
    else if (guid == CKPGUID_COMBINE3TEX)
        return "CKPGUID_COMBINE3TEX";
    else if (guid == CKPGUID_BUMPMAPPARAM)
        return "CKPGUID_BUMPMAPPARAM";
    else if (guid == CKPGUID_TEXCOMBINE)
        return "CKPGUID_TEXCOMBINE";
    else if (guid == CKPGUID_PIXELFORMAT)
        return "CKPGUID_PIXELFORMAT";
    else if (guid == CKPGUID_AXIS)
        return "CKPGUID_AXIS";
    else if (guid == CKPGUID_SUPPORT)
        return "CKPGUID_SUPPORT";
    else if (guid == CKPGUID_BITMAP_SYSTEMCACHING)
        return "CKPGUID_BITMAP_SYSTEMCACHING";
    else if (guid == CKPGUID_OLDMESSAGE)
        return "CKPGUID_OLDMESSAGE";
    else if (guid == CKPGUID_OLDATTRIBUTE)
        return "CKPGUID_OLDATTRIBUTE";
    else
    {
        static char buf[512];
        std::sprintf(buf, "CKGUID(%#lx,%#lx)", guid.d1, guid.d2);
        return buf;
    }
}

static const char *GetBehaviorPrototypeFlagsName(CK_BEHAVIORPROTOTYPE_FLAGS flag)
{
    switch (flag)
    {
    case CK_BEHAVIORPROTOTYPE_NORMAL:
        return "CK_BEHAVIORPROTOTYPE_NORMAL";
    case CK_BEHAVIORPROTOTYPE_HIDDEN:
        return "CK_BEHAVIORPROTOTYPE_HIDDEN";
    case CK_BEHAVIORPROTOTYPE_OBSOLETE:
        return "CK_BEHAVIORPROTOTYPE_OBSOLETE";
    default:
    {
        static char buf[512];
        std::sprintf(buf, "%d", flag);
        return buf;
    }
    }
}

static const char *GetBehaviorFlagsName(CK_BEHAVIOR_FLAGS flag)
{
    switch (flag)
    {
    case CKBEHAVIOR_NONE:
        return "CKBEHAVIOR_NONE";
    case CKBEHAVIOR_ACTIVE:
        return "CKBEHAVIOR_ACTIVE";
    case CKBEHAVIOR_SCRIPT:
        return "CKBEHAVIOR_SCRIPT";
    case CKBEHAVIOR_RESERVED1:
        return "CKBEHAVIOR_RESERVED1";
    case CKBEHAVIOR_USEFUNCTION:
        return "CKBEHAVIOR_USEFUNCTION";
    case CKBEHAVIOR_RESERVED2:
        return "CKBEHAVIOR_RESERVED2";
    case CKBEHAVIOR_CUSTOMSETTINGSEDITDIALOG:
        return "CKBEHAVIOR_CUSTOMSETTINGSEDITDIALOG";
    case CKBEHAVIOR_WAITSFORMESSAGE:
        return "CKBEHAVIOR_WAITSFORMESSAGE";
    case CKBEHAVIOR_VARIABLEINPUTS:
        return "CKBEHAVIOR_VARIABLEINPUTS";
    case CKBEHAVIOR_VARIABLEOUTPUTS:
        return "CKBEHAVIOR_VARIABLEOUTPUTS";
    case CKBEHAVIOR_VARIABLEPARAMETERINPUTS:
        return "CKBEHAVIOR_VARIABLEPARAMETERINPUTS";
    case CKBEHAVIOR_VARIABLEPARAMETEROUTPUTS:
        return "CKBEHAVIOR_VARIABLEPARAMETEROUTPUTS";
    case CKBEHAVIOR_TOPMOST:
        return "CKBEHAVIOR_TOPMOST";
    case CKBEHAVIOR_BUILDINGBLOCK:
        return "CKBEHAVIOR_BUILDINGBLOCK";
    case CKBEHAVIOR_MESSAGESENDER:
        return "CKBEHAVIOR_MESSAGESENDER";
    case CKBEHAVIOR_MESSAGERECEIVER:
        return "CKBEHAVIOR_MESSAGERECEIVER";
    case CKBEHAVIOR_TARGETABLE:
        return "CKBEHAVIOR_TARGETABLE";
    case CKBEHAVIOR_CUSTOMEDITDIALOG:
        return "CKBEHAVIOR_CUSTOMEDITDIALOG";
    case CKBEHAVIOR_RESERVED0:
        return "CKBEHAVIOR_RESERVED0";
    case CKBEHAVIOR_EXECUTEDLASTFRAME:
        return "CKBEHAVIOR_EXECUTEDLASTFRAME";
    case CKBEHAVIOR_DEACTIVATENEXTFRAME:
        return "CKBEHAVIOR_DEACTIVATENEXTFRAME";
    case CKBEHAVIOR_RESETNEXTFRAME:
        return "CKBEHAVIOR_RESETNEXTFRAME";
    case CKBEHAVIOR_INTERNALLYCREATEDINPUTS:
        return "CKBEHAVIOR_INTERNALLYCREATEDINPUTS";
    case CKBEHAVIOR_INTERNALLYCREATEDOUTPUTS:
        return "CKBEHAVIOR_INTERNALLYCREATEDOUTPUTS";
    case CKBEHAVIOR_INTERNALLYCREATEDINPUTPARAMS:
        return "CKBEHAVIOR_INTERNALLYCREATEDINPUTPARAMS";
    case CKBEHAVIOR_INTERNALLYCREATEDOUTPUTPARAMS:
        return "CKBEHAVIOR_INTERNALLYCREATEDOUTPUTPARAMS";
    case CKBEHAVIOR_INTERNALLYCREATEDLOCALPARAMS:
        return "CKBEHAVIOR_INTERNALLYCREATEDLOCALPARAMS";
    case CKBEHAVIOR_ACTIVATENEXTFRAME:
        return "CKBEHAVIOR_ACTIVATENEXTFRAME";
    case CKBEHAVIOR_LOCKED:
        return "CKBEHAVIOR_LOCKED";
    case CKBEHAVIOR_LAUNCHEDONCE:
        return "CKBEHAVIOR_LAUNCHEDONCE";
    default:
    {
        static char buf[512];
        std::sprintf(buf, "%d", flag);
        return buf;
    }
    }
}

bool BuildingBlock::Load()
{
    CKObjectDeclaration *od = CKGetObjectDeclarationFromGuid(m_Guid);
    if (!od) return false;

    m_Name = od->GetName();
    m_Description = od->GetDescription();
    m_Category = od->GetCategory();
    m_AuthorGuid = od->GetAuthorGuid();
    m_Author = od->GetAuthorName();
    m_Version = od->GetVersion();
    m_CompatibleClassId = od->GetCompatibleClassId();

    for (int i = 0; i < od->GetManagerNeededCount(); ++i)
        AddManagerNeeded(od->GetManagerNeeded(i));

    CKBehaviorPrototype *proto = CKGetPrototypeFromGuid(m_Guid);
    if (!proto) return false;

    m_PrototypeName = proto->GetName();

    auto *inIos = proto->GetInIOList();
    for (int i = 0; i < proto->GetInputCount(); ++i)
        AddInput(inIos[i]->Name);

    auto *outIos = proto->GetOutIOList();
    for (int i = 0; i < proto->GetOutputCount(); ++i)
        AddOutput(outIos[i]->Name);

    auto *inParams = proto->GetInParameterList();
    for (int i = 0; i < proto->GetInParameterCount(); ++i)
        AddInputParam(inParams[i]->Name, inParams[i]->Guid, inParams[i]->DefaultValueString);

    auto *outParams = proto->GetOutParameterList();
    for (int i = 0; i < proto->GetOutParameterCount(); ++i)
        AddOutputParam(outParams[i]->Name, outParams[i]->Guid, outParams[i]->DefaultValueString);

    auto *localParams = proto->GetLocalParameterList();
    for (int i = 0; i < proto->GetLocalParameterCount(); ++i)
    {
        if (localParams[i]->Type == CKPARAMETER_LOCAL)
            AddLocalParam(localParams[i]->Name, localParams[i]->Guid, localParams[i]->DefaultValueString);
        else if (localParams[i]->Type == CKPARAMETER_SETTING)
            AddSetting(localParams[i]->Name, localParams[i]->Guid, localParams[i]->DefaultValueString);
    }

    m_Function = proto->GetFunction();
    m_Callback = proto->GetBehaviorCallbackFct();
    m_Flags = proto->GetFlags();
    m_BehaviorFlags = proto->GetBehaviorFlags();

    return true;
}

bool BuildingBlock::Dump(const char *filename, const char *dir)
{
    if (filename == nullptr) filename = "";
    if (dir == nullptr) dir = "";

    std::string name;
    name.reserve(m_Name.size());
    for (auto &ch : m_Name)
        if (std::isalnum(ch))
            name.push_back(ch);

    std::string path(512, '\0');
    VxGetCurrentDirectory(path.data());
    path.resize(path.find('\0'));
    path.push_back('\\');
    path.append(dir);
    path.push_back('\\');
    VxMakeDirectory(path.data());
    if (strcmp(filename, "") != 0)
    {
        path.append(filename);
    }
    else
    {
        path.append(name);
        path.append(".cpp");
    }

    FILE *fp = std::fopen(path.c_str(), "w");
    if (!fp) return false;

    printfCommentSquare(fp, m_Name);

    std::fputs("#include \"CKAll.h\"\n\n", fp);

    std::string fillDeclFctDecl = std::string("CKObjectDeclaration *FillBehavior") + name + "Decl()";
    std::string createProtoFctName = std::string("Create") + name + "Proto";
    std::string createProtoFctDecl = std::string("CKERROR ") + createProtoFctName + "(CKBehaviorPrototype **pproto)";
    std::string fctDecl = std::string("int ") + name + "(const CKBehaviorContext& behcontext)";
    std::string callbackName = name + "CallBack";
    std::string callbackDecl = std::string("CKERROR ") + callbackName + "(const CKBehaviorContext& behcontext)";

    std::fprintf(fp, "%s;\n", fillDeclFctDecl.c_str());
    std::fprintf(fp, "%s;\n", createProtoFctDecl.c_str());
    std::fprintf(fp, "%s;\n", fctDecl.c_str());
    if (m_Callback != nullptr)
        std::fprintf(fp, "%s;\n", callbackDecl.c_str());
    std::fputc('\n', fp);

    std::fprintf(fp, "%s\n", fillDeclFctDecl.c_str());
    std::fputs("{\n", fp);
    std::fprintf(fp, "\tCKObjectDeclaration *od = CreateCKObjectDeclaration(\"%s\");\n", m_Name.c_str());
    std::fprintf(fp, "\tod->SetDescription(\"%s\");\n", m_Description.c_str());
    std::fprintf(fp, "\tod->SetCategory(\"%s\");\n", m_Category.c_str());
    std::fprintf(fp, "\tod->SetType(CKDLL_BEHAVIORPROTOTYPE);\n");
    std::fprintf(fp, "\tod->SetGuid(CKGUID(%#lx,%#lx));\n", m_Guid.d1, m_Guid.d2);
    std::fprintf(fp, "\tod->SetAuthorGuid(CKGUID(%#lx,%#lx));\n", m_AuthorGuid.d1, m_AuthorGuid.d2);
    std::fprintf(fp, "\tod->SetAuthorName(\"%s\");\n", m_Author.c_str());
    std::fprintf(fp, "\tod->SetVersion(%#.8lx);\n", m_Version);
    std::fprintf(fp, "\tod->SetCreationFunction(%s);\n", createProtoFctName.c_str());
    std::fprintf(fp, "\tod->SetCompatibleClassId(%s);\n", GetClassIdentifierName(m_CompatibleClassId));
    if (!m_ManagerNeeded.empty())
    {
        for (auto &guid : m_ManagerNeeded)
            std::fprintf(fp, "\tod->NeedManager(%s);\n", GetManagerGuidName(guid));
    }
    std::fputs("\treturn od;\n", fp);
    std::fputs("}\n\n", fp);

    std::fprintf(fp, "%s\n", createProtoFctDecl.c_str());
    std::fputs("{\n", fp);
    std::fprintf(fp, "\tCKBehaviorPrototype *proto = CreateCKBehaviorPrototype(\"%s\");\n", m_PrototypeName.c_str());
    std::fprintf(fp, "\tif (!proto) return CKERR_OUTOFMEMORY;\n\n");
    for (auto &input : m_Inputs)
    {
        std::fprintf(fp, "\tproto->DeclareInput(\"%s\");\n", input.c_str());
    }
    if (!m_Inputs.empty())
        std::fputc('\n', fp);

    for (auto &output : m_Outputs)
    {
        std::fprintf(fp, "\tproto->DeclareOutput(\"%s\");\n", output.c_str());
    }
    if (!m_Outputs.empty())
        std::fputc('\n', fp);

    for (auto &param : m_InputParams)
    {
        if (param.value.empty())
            std::fprintf(fp, "\tproto->DeclareInParameter(\"%s\", %s);\n", param.name.c_str(), GetPreregisteredParameterTypeName(param.type));
        else
            std::fprintf(fp, "\tproto->DeclareInParameter(\"%s\", %s, \"%s\");\n", param.name.c_str(), GetPreregisteredParameterTypeName(param.type), param.value.c_str());
    }
    if (!m_InputParams.empty())
        std::fputc('\n', fp);

    for (auto &param : m_OutputParams)
    {
        if (param.value.empty())
            std::fprintf(fp, "\tproto->DeclareOutParameter(\"%s\", %s);\n", param.name.c_str(), GetPreregisteredParameterTypeName(param.type));
        else
            std::fprintf(fp, "\tproto->DeclareOutParameter(\"%s\", %s, \"%s\");\n", param.name.c_str(), GetPreregisteredParameterTypeName(param.type), param.value.c_str());
    }
    if (!m_OutputParams.empty())
        std::fputc('\n', fp);

    for (auto &param : m_LocalParams)
    {
        if (param.value.empty())
            std::fprintf(fp, "\tproto->DeclareLocalParameter(\"%s\", %s);\n", param.name.c_str(), GetPreregisteredParameterTypeName(param.type));
        else
            std::fprintf(fp, "\tproto->DeclareLocalParameter(\"%s\", %s, \"%s\");\n", param.name.c_str(), GetPreregisteredParameterTypeName(param.type), param.value.c_str());
    }
    if (!m_LocalParams.empty())
        std::fputc('\n', fp);

    for (auto &param : m_Settings)
    {
        if (param.value.empty())
            std::fprintf(fp, "\tproto->DeclareSetting(\"%s\", %s);\n", param.name.c_str(), GetPreregisteredParameterTypeName(param.type));
        else
            std::fprintf(fp, "\tproto->DeclareSetting(\"%s\", %s, \"%s\");\n", param.name.c_str(), GetPreregisteredParameterTypeName(param.type), param.value.c_str());
    }
    if (!m_Settings.empty())
        std::fputc('\n', fp);

    {
        std::fprintf(fp, "\tproto->SetFlags(");
        std::string flags;
        for (int i = 0; i < 3; ++i)
        {
            auto flag = static_cast<CK_BEHAVIORPROTOTYPE_FLAGS>(1 << i);
            if ((m_Flags & flag) != 0)
            {
                flags += GetBehaviorPrototypeFlagsName(flag);
                flags += " | ";
            }
        }
        flags.erase(flags.size() - 3);
        std::fprintf(fp, "%s);\n", flags.c_str());
    }

    std::fprintf(fp, "\tproto->SetFunction(%s);\n\n", name.c_str());

    if (m_BehaviorFlags != CKBEHAVIOR_NONE)
    {
        std::fprintf(fp, "\tproto->SetBehaviorFlags((CK_BEHAVIOR_FLAGS)(");
        std::string flags;
        for (int i = 0; i < 30; ++i)
        {
            auto flag = static_cast<CK_BEHAVIOR_FLAGS>(1 << i);
            if ((m_BehaviorFlags & flag) != 0)
            {
                flags += GetBehaviorFlagsName(flag);
                flags += " | ";
            }
        }
        flags.erase(flags.size() - 3);
        std::fprintf(fp, "%s));\n", flags.c_str());
    }

    if (m_Callback != nullptr)
        std::fprintf(fp, "\tproto->SetBehaviorCallbackFct(%s);\n\n", callbackName.c_str());
    else
        std::fputc('\n', fp);

    std::fputs("\t*pproto = proto;\n", fp);
    std::fputs("\treturn CK_OK;\n", fp);
    std::fputs("}\n\n", fp);

    std::fprintf(fp, "%s\n", fctDecl.c_str());
    std::fputs("{\n\tCKBehavior *beh = behcontext.Behavior;\n\t// TODO: Please finish it manually.\n\treturn CKBR_OK;\n}\n\n", fp);

    if (m_Callback != nullptr)
    {
        std::fprintf(fp, "%s\n", callbackDecl.c_str());
        std::fputs("{\n\tCKBehavior *beh = behcontext.Behavior;\n\t// TODO: Please finish it manually.\n\treturn CKBR_OK;\n}", fp);
    }

    std::fclose(fp);

    return true;
}