﻿#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include "omokobj_manage.h"
#include "omokobj_judge.h"

/**
* @file omokobj_manage.c
*/


/**************************************************
*			OmokCoord Management def
***************************************************/

OmokCoord _OmokCoord(char row, short col)
{
	OmokCoord obj = { 0, 0 };
	if (isalpha(row))
		obj.row = toupper(row);
	if (1 <= col && col <= 19)
		obj.col = col;
	return obj;
}

void set_OmokCoord(OmokCoord* obj, char row, short col)
{
	*obj = _OmokCoord(row, col);
}

OmokCoord _sOmokCoord(const char* str)
{
	OmokCoord obj = { 0, 0 };
	if (isalpha(str[0]))
		obj.row = toupper(str[0]);
	
	if (isdigit(str[1]))
	{
		if (strlen(str) == 2)
			obj.col = atoi(str + 1);
		else if (strlen(str) == 3 && isdigit(str[2]))
			obj.col = atoi(str + 1);
	}
	return obj;
	
}

void set_sOmokCoord(OmokCoord* obj, const char* set)
{
	*obj = _sOmokCoord(set);
}



/**************************************************
*			StoneType Management def
***************************************************/

StoneType _sStoneType(const char* str)
{
	StoneType obj = ERR_ST;
	char* valid_arg[] = {
		"w", "W", "white", "White", "B", "b", "black", "Black"
	};

	for (int i = 0; i < 8; i++)	
	{
		if (strcmp(str, valid_arg[i]) == 0) 
		{
			obj = i < 4 ? White : Black;
			break;
		}
	}

	return obj;
}



/**************************************************
*			OmokCursor Management def
***************************************************/

OmokCursor _OmokCursor(OmokCoord locate, StoneType type)
{
	OmokCursor obj = { locate, type };
	return obj;
}

void set_OmokCursor(OmokCursor* obj, OmokCoord locate, StoneType type)
{
	*obj = _OmokCursor(locate, type);
}

OmokCursor _sOmokCursor(const char* locate, const char* type)
{
	OmokCursor obj = { _sOmokCoord(locate), _sStoneType(type) };
	return obj;
}

void set_sOmokCursor(OmokCursor* obj, const char* locate, const char* type)
{
	*obj = _sOmokCursor(locate, type);
}

OmokCursor Stone_to_OmokCursor(Stone* obj)
{
	OmokCursor result = { obj->locate, obj->type };
	return result;
}



/**************************************************
*			Stone Management def
***************************************************/

Stone _Stone(OmokCoord locate, StoneType type)
{
	Stone obj = { locate, type };
	return obj;
}

void set_Stone(Stone* obj, OmokCoord locate, StoneType type)
{
	obj->locate = locate;
	obj->type = type;
}

Stone _sStone(const char* locate, const char* type)
{
	Stone obj = { _sOmokCoord(locate), _sStoneType(type) };
	return obj;
}

void set_sStone(Stone* obj, const char* locate, const char* type)
{
	*obj = _sStone(locate, type);
}

Stone OmokCursor_to_Stone(OmokCursor* obj)
{
	Stone result = { obj->locate, obj->type };
	return result;
}



/**************************************************
*			StoneNode Management def
***************************************************/

StoneNode _StoneNode(Stone stone, StoneNode* next)
{
	StoneNode obj = { 0, stone, next };
	return obj;
}

void set_StoneNode(StoneNode* obj, Stone stone, StoneNode* next)
{
	obj->stone = stone;
	obj->next = next;
}

StoneNode* new_StoneNode(StoneNode obj)
{
	StoneNode* result = (StoneNode*)malloc(sizeof(StoneNode));
	if (result != NULL)
	{
		*result = obj;			//우선 얕은 복사 수행
		result->is_dynamic = 1; //result는 동적 할당 객체이므로.
	}

	return result;
}

int free_StoneNode(StoneNode* obj)
{
	//인자로 전달된 객체가 NULL이 아니고 동적 할당 객체여야 free 가능
	if (is_StoneNode_dynamic(obj))
	{
		//free하기 전 NextNode에 동적 할당 객체가 연결되어 있을 경우, 우선 NextNode를 해제함
		if (is_StoneNode_dynamic(obj->next))
		{
			// nextNode가 정상 해제되지 않았을 경우
			if (!free_StoneNode(obj->next)) 
				return 0;
		}

		free(obj);
		return 1;
	}
	else
		return 0;
}

StoneNode* detach_nextStoneNode(StoneNode* obj)
{
	StoneNode* detached_node = obj->next;
	obj->next = NULL;
	return detached_node;
}

int attach_nextStoneNode(StoneNode* obj, StoneNode* target)
{
	if (obj->next == NULL && is_StoneNode_dynamic(target))
	{
		obj->next = target;
		return 1;
	}
	else 
		return 0;
}

StoneNode* deepcopy_StoneNode(StoneNode* obj)
{
	StoneNode* result = NULL;
	
	//obj이 동적 할당 객체일 경우 작업 수행
	if (is_StoneNode_dynamic(obj))
	{
		//우선 obj의 정보로 동적 할당 객체 생성
		//얕은 복사임
		result = new_StoneNode(*obj);

		//생성이 잘 이루어졌다면
		if (result != NULL)
		{
			//obj의 nextNode가 있을 경우 재귀적으로 깊은 복사 수행함
			if (obj->next != NULL)
			{
				result->next = deepcopy_StoneNode(obj->next);

				//재귀적 깊은 복사가 실패했을 경우 반환할 객체를 NULL으로 설정
				if (result->next == NULL)
				{
					free_StoneNode(result);
					result = NULL;
				}
			}
		}
	}

	return result;
}



/**************************************************
*			StoneList Management def
***************************************************/

StoneList _StoneList(int size, StoneNode* header)
{
	StoneList obj = { 0, size, header };
	return obj;
}

StoneList* new_StoneList(StoneList obj)
{
	return 0;
}

int free_StoneList(StoneList* obj)
{
	return 0;
}

int addNode_to(StoneList* list, StoneNode node)
{
	return 0;
}

int deleteNode_from(StoneList* list, StoneNode node)
{
	return 0;
}

int clearallNode_from(StoneList* list)
{
	return 0;
}

int deepcopy_StoneList(StoneList* obj, StoneList* target)
{
	return 0;
}



/**************************************************
*			OmokPanelType Management def
***************************************************/

OmokPanelType _sOmokPanelType(const char* str)
{
	OmokPanelType obj = ERR_OPT;
	const char* valid_arg[] = {
		"regular", "r", "Regular", "R", 
		"jumbo", "j", "Jumbo", "J"
	};

	for (int i = 0; i < 8; i++)
		if (strcmp(str, valid_arg[i]) == 0)
			obj = i < 4 ? regular : jumbo;

	return obj;
}



/**************************************************
*			OmokPanel Management def
***************************************************/

int init_OmokPanel(OmokPanel* obj, OmokPanelType type)
{
	return 0;
}

int finalize_OmokPanel(OmokPanel* obj)
{
	return 0;
}

int deepcopy_OmokPanel(OmokPanel* obj, OmokPanel* target)
{
	return 0;
}

int modify_type_OmokPanel(OmokPanel* obj, OmokPanelType type)
{
	return 0;
}

int addStone_to(OmokPanel* panel, Stone stone)
{
	return 0;
}

StoneType lookupStone_from(OmokPanel* panel, OmokCoord locate)
{
	return ERR_ST;
}

StoneType deleteStone_from(OmokPanel* panel, OmokCoord locate)
{
	return ERR_ST;
}

int clearallStone_from(OmokPanel* obj)
{
	return 0;
}

StoneNode* get_StoneNodeptr_from(OmokPanel* panel, OmokCoord locate)
{
	return NULL;
}



/**************************************************
*			OmokStatus Management def
***************************************************/

int init_OmokStatus(OmokStatus* obj)
{
	return 0;
}

int finalize_OmokStatus(OmokStatus* obj)
{
	return 0;
}
 
int deepcopy_OmokStatus(OmokStatus* obj, OmokStatus* target)
{
	return 0;
}
 
int clear_OmokStatus(OmokStatus* obj)
{
	return 0;
}
 
int turns_up(OmokStatus* obj, StoneNode* released)
{
	return 0;
}
 
StoneNode* turns_down(OmokStatus* obj)
{
	return NULL;
}
 
int ordersize_up(OmokStatus* obj)
{
	return 0;
}
 
int ordersize_down(OmokStatus* obj)
{
	return 0;
}
 
int get_turns(OmokStatus* obj)
{
	return 0;
}
 
int get_ordersize(OmokStatus* obj)
{
	return 0;
}
 
Stone get_StoneInfo_from(OmokStatus* obj, int turns)
{
	Stone result = { _sOmokCoord("") , ERR_ST };
	return result;
}
 



/**************************************************
*			OmokStatus Management def
***************************************************/

int init_Omok(Omok* obj, OmokPanelType type)
{
	return 0;
}
 
int finalize_Omok(Omok* obj)
{
	return 0;
}
 
int deepcopy_Omok(Omok* obj, Omok* target)
{
	return 0;
}
 
