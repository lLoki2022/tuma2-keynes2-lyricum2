#include "StdAfx.h"
#include "../eterBase/CRC32.h"
#include "../eterBase/Filename.h"
#include "PythonWindow.h"
#include "PythonSlotWindow.h"
#include "../UserInterface/Locale_inc.h"

//#define __RENDER_SLOT_AREA__

using namespace UI;

class UI::CSlotWindow::CSlotButton : public CButton
{
	public:
		enum ESlotButtonType
		{
			SLOT_BUTTON_TYPE_PLUS,
			SLOT_BUTTON_TYPE_COVER,
		};

	public:
		CSlotButton(ESlotButtonType dwType, DWORD dwSlotNumber, CSlotWindow * pParent) : CButton(NULL)
		{
			m_dwSlotButtonType = dwType;
			m_dwSlotNumber = dwSlotNumber;
			m_pParent = pParent;
		}
		virtual ~CSlotButton()
		{
		}

		BOOL OnMouseLeftButtonDown()
		{
			if (!IsEnable())
				return TRUE;
			if (UI::CWindowManager::Instance().IsAttaching())
				return TRUE;

			m_isPressed = TRUE;
			Down();

			return TRUE;
		}
		BOOL OnMouseLeftButtonUp()
		{
			if (!IsEnable())
				return TRUE;
			if (!IsPressed())
				return TRUE;

			if (IsIn())
				SetCurrentVisual(&m_overVisual);
			else
				SetCurrentVisual(&m_upVisual);

			m_pParent->OnPressedSlotButton(m_dwSlotButtonType, m_dwSlotNumber);

			return TRUE;
		}

		void OnMouseOverIn()
		{
			if (IsEnable())
			{
				SetCurrentVisual(&m_overVisual);
			}

			if (m_pParent->OnOverInItem(m_dwSlotNumber) == FALSE)
			{
				m_pParent->OnOverInEmptySlot(m_dwSlotNumber);
			}
		}
		void OnMouseOverOut()
		{
			if (IsEnable())
			{
				SetUp();
				SetCurrentVisual(&m_upVisual);
			}
			m_pParent->OnOverOutItem();
			m_pParent->OnOverOutEmptySlot();
		}

	protected:
		ESlotButtonType m_dwSlotButtonType;
		DWORD m_dwSlotNumber;
		CSlotWindow * m_pParent;
};

///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

class UI::CSlotWindow::CCoverButton : public CSlotButton
{
	public:
		CCoverButton(ESlotButtonType dwType, DWORD dwSlotNumber, CSlotWindow * pParent) : CSlotButton(dwType, dwSlotNumber, pParent)
		{
			m_bLeftButtonEnable = TRUE;
			m_bRightButtonEnable = TRUE;
		}
		virtual ~CCoverButton()
		{
		}

		void SetLeftButtonEnable(BOOL bEnable)
		{
			m_bLeftButtonEnable = bEnable;
		}
		void SetRightButtonEnable(BOOL bEnable)
		{
			m_bRightButtonEnable = bEnable;
		}

		void OnRender()
		{
		}

		void RenderButton()
		{
			CButton::OnRender();
		}

		BOOL OnMouseLeftButtonDown()
		{
			if (!IsEnable())
				return TRUE;
			if (m_bLeftButtonEnable)
			{
				CButton::OnMouseLeftButtonDown();
			}
			else
			{
				m_pParent->OnMouseLeftButtonDown();
			}
			return TRUE;
		}
		BOOL OnMouseLeftButtonUp()
		{
			if (!IsEnable())
				return TRUE;
			if (m_bLeftButtonEnable)
			{
				CButton::OnMouseLeftButtonUp();
				m_pParent->OnMouseLeftButtonDown();
			}
			else
			{
				m_pParent->OnMouseLeftButtonUp();
			}
			return TRUE;
		}

		BOOL OnMouseRightButtonDown()
		{
			if (!IsEnable())
				return TRUE;
			if (m_bRightButtonEnable)
				CButton::OnMouseLeftButtonDown();
			return TRUE;
		}
		BOOL OnMouseRightButtonUp()
		{
			if (!IsEnable())
				return TRUE;
			m_pParent->OnMouseRightButtonDown();
			if (m_bRightButtonEnable)
				CButton::OnMouseLeftButtonUp();
			return TRUE;
		}

	protected:
		BOOL m_bLeftButtonEnable;
		BOOL m_bRightButtonEnable;
};

///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

class UI::CSlotWindow::CCoolTimeFinishEffect : public CAniImageBox
{
	public:
		CCoolTimeFinishEffect(CSlotWindow * pParent, DWORD dwSlotIndex) : CAniImageBox(NULL)
		{
			m_pParent = pParent;
			m_dwSlotIndex = dwSlotIndex;
		}
		virtual ~CCoolTimeFinishEffect()
		{
		}

		void OnEndFrame()
		{
			((CSlotWindow *)m_pParent)->ReserveDestroyCoolTimeFinishEffect(m_dwSlotIndex);
		}

	protected:
		DWORD m_dwSlotIndex;
};

///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

// Set & Append

#ifdef WJ_ENABLE_TRADABLE_ICON
void CSlotWindow::SetCanMouseEventSlot(DWORD dwIndex)
{
	TSlot * pSlot;
	if (!GetSlotPointer(dwIndex, &pSlot))
		return;

	REMOVE_BIT(pSlot->dwState, SLOT_STATE_CANT_MOUSE_EVENT);
	//pSlot->dwState |= SLOT_STATE_CANT_MOUSE_EVENT;
}

void CSlotWindow::SetCantMouseEventSlot(DWORD dwIndex)
{
	TSlot * pSlot;
	if (!GetSlotPointer(dwIndex, &pSlot))
		return;

	SET_BIT(pSlot->dwState, SLOT_STATE_CANT_MOUSE_EVENT);
	//pSlot->dwState ^= SLOT_STATE_CANT_MOUSE_EVENT;
}

void CSlotWindow::SetUsableSlotOnTopWnd(DWORD dwIndex)
{
	TSlot * pSlot;
	if (!GetSlotPointer(dwIndex, &pSlot))
		return;

	REMOVE_BIT(pSlot->dwState, SLOT_STATE_UNUSABLE);
	//pSlot->dwState |= SLOT_STATE_UNUSABLE;
}

void CSlotWindow::SetUnusableSlotOnTopWnd(DWORD dwIndex)
{
	TSlot * pSlot;
	if (!GetSlotPointer(dwIndex, &pSlot))
		return;

	SET_BIT(pSlot->dwState, SLOT_STATE_UNUSABLE);
	//pSlot->dwState ^= SLOT_STATE_UNUSABLE;
}
#endif

void CSlotWindow::SetSlotType(DWORD dwType)
{
	m_dwSlotType = dwType;
}

void CSlotWindow::SetSlotStyle(DWORD dwStyle)
{
	m_dwSlotStyle = dwStyle;
}

void CSlotWindow::AppendSlot(DWORD dwIndex, int ixPosition, int iyPosition, int ixCellSize, int iyCellSize)
{
	TSlot Slot;
	Slot.pInstance = NULL;
	Slot.pNumberLine = NULL;
	Slot.pCoverButton = NULL;
	Slot.pSlotButton = NULL;
	Slot.pSignImage = NULL;
	Slot.pFinishCoolTimeEffect = NULL;
#if defined(ENABLE_HIGHLIGHT_SYSTEM)
	Slot.pNewSlotEffect.fill(nullptr);
#endif
	ClearSlot(&Slot);
	Slot.dwSlotNumber = dwIndex;
	Slot.dwCenterSlotNumber = dwIndex;
	Slot.ixPosition = ixPosition;
	Slot.iyPosition = iyPosition;
	Slot.ixCellSize = ixCellSize;
	Slot.iyCellSize = iyCellSize;
	m_SlotList.push_back(Slot);
}

void CSlotWindow::SetCoverButton(DWORD dwIndex, const char * c_szUpImageName, const char * c_szOverImageName, const char * c_szDownImageName, const char * c_szDisableImageName, BOOL bLeftButtonEnable, BOOL bRightButtonEnable)
{
	TSlot * pSlot;
	if (!GetSlotPointer(dwIndex, &pSlot))
		return;

	CCoverButton *& rpCoverButton = pSlot->pCoverButton;

	if (!rpCoverButton)
	{
		rpCoverButton = new CCoverButton(CSlotButton::SLOT_BUTTON_TYPE_COVER, pSlot->dwSlotNumber, this);
		CWindowManager::Instance().SetParent(rpCoverButton, this);
	}

	rpCoverButton->SetLeftButtonEnable(bLeftButtonEnable);
	rpCoverButton->SetRightButtonEnable(bRightButtonEnable);
	rpCoverButton->SetUpVisual(c_szUpImageName);
	rpCoverButton->SetOverVisual(c_szOverImageName);
	rpCoverButton->SetDownVisual(c_szDownImageName);
	rpCoverButton->SetDisableVisual(c_szDisableImageName);
	rpCoverButton->Enable();
	rpCoverButton->Show();

	// NOTE : Cover ��o����AI Plus ��o����A�� �Ƣ���A��o��A���� AO��A AU��a��|..
	if (pSlot->pSlotButton)
	{
		SetTop(pSlot->pSlotButton);
	}
}

void CSlotWindow::EnableCoverButton(DWORD dwIndex)
{
	TSlot * pSlot;
	if (!GetSlotPointer(dwIndex, &pSlot))
		return;

	if (!pSlot->pCoverButton)
		return;

	pSlot->pCoverButton->Enable();
}

void CSlotWindow::DisableCoverButton(DWORD dwIndex)
{
	TSlot * pSlot;
	if (!GetSlotPointer(dwIndex, &pSlot))
		return;

	if (!pSlot->pCoverButton)
		return;

	pSlot->pCoverButton->Disable();
}

#if defined(ENABLE_NEW_FISH_EVENT)
void CSlotWindow::DeleteCoverButton(uint32_t index) {
	TSlot* pSlot;
	if (!GetSlotPointer(index, &pSlot)) {
		return;
	}

	if (!pSlot->pCoverButton) {
		return;
	}

	CWindowManager::Instance().DestroyWindow(pSlot->pCoverButton);
	pSlot->pCoverButton = NULL;
}
#endif

void CSlotWindow::SetAlwaysRenderCoverButton(DWORD dwIndex, bool bAlwaysRender)
{
	TSlot * pSlot;
	if (!GetSlotPointer(dwIndex, &pSlot))
		return;

	if (bAlwaysRender)
		SET_BIT(pSlot->dwState, SLOT_STATE_ALWAYS_RENDER_COVER);
	else
		REMOVE_BIT(pSlot->dwState, SLOT_STATE_ALWAYS_RENDER_COVER);
}

void CSlotWindow::ShowSlotBaseImage(DWORD dwIndex)
{
	TSlot * pSlot;
	if (!GetSlotPointer(dwIndex, &pSlot))
		return;

	pSlot->bRenderBaseSlotImage = true;
}

void CSlotWindow::HideSlotBaseImage(DWORD dwIndex)
{
	TSlot * pSlot;
	if (!GetSlotPointer(dwIndex, &pSlot))
		return;

	pSlot->bRenderBaseSlotImage = false;
}

BOOL CSlotWindow::IsDisableCoverButton(DWORD dwIndex)
{
	TSlot * pSlot;
	if (!GetSlotPointer(dwIndex, &pSlot))
		return FALSE;

	if (!pSlot->pCoverButton)
		return FALSE;

	return pSlot->pCoverButton->IsDisable();
}

void CSlotWindow::SetSlotBaseImage(const char * c_szFileName, float fr, float fg, float fb, float fa)
{
	__CreateBaseImage(c_szFileName, fr, fg, fb, fa);
}


#ifdef NEW_PET_SYSTEM
void CSlotWindow::SetSlotBaseImageScale(const char * c_szFileName, float fr, float fg, float fb, float fa, float sx, float sy)
{
	__CreateBaseImageScale(c_szFileName, fr, fg, fb, fa, sx, sy);
}
#endif

void CSlotWindow::AppendSlotButton(const char * c_szUpImageName, const char * c_szOverImageName, const char * c_szDownImageName)
{
	for (TSlotListIterator itor = m_SlotList.begin(); itor != m_SlotList.end(); ++itor)
	{
		TSlot & rSlot = *itor;
		CSlotButton *& rpSlotButton = rSlot.pSlotButton;

		if (!rpSlotButton)
		{
			rpSlotButton = new CSlotButton(CSlotButton::SLOT_BUTTON_TYPE_PLUS, rSlot.dwSlotNumber, this);
			rpSlotButton->AddFlag(FLAG_FLOAT);
			CWindowManager::Instance().SetParent(rpSlotButton, this);
		}

		rpSlotButton->SetUpVisual(c_szUpImageName);
		rpSlotButton->SetOverVisual(c_szOverImageName);
		rpSlotButton->SetDownVisual(c_szDownImageName);
		rpSlotButton->SetPosition(rSlot.ixPosition + 1, rSlot.iyPosition + 19);
		rpSlotButton->Hide();
	}
}

#if defined(ENABLE_OFFLINESHOP_REWORK)
int CSlotWindow::FindEmptyGrid(BYTE bSizeItem)
{
	if (!m_pGrid)
		return 0;

	return m_pGrid->FindBlank(1, bSizeItem);
}

void CSlotWindow::PutItemGrid(int iPos, BYTE bSizeItem)
{
	if (!m_pGrid)
		return;

	m_pGrid->Put(iPos, 1, bSizeItem);
}

void CSlotWindow::RemoveItemGrid(int iPos, BYTE bSizeItem)
{
	if (!m_pGrid)
		return;

	m_pGrid->Get(iPos, 1, bSizeItem);
}

void CSlotWindow::ClearItemGrid()
{
	if (!m_pGrid)
		return;

	m_pGrid->Clear();
}

void CSlotWindow::SetGridWindow(int w, int h)
{
	if (m_pGrid)
	{
		m_pGrid.release();
		m_pGrid = nullptr;
	}

	m_pGrid = std::make_unique<CGrid>(w, h);
}
#endif

void CSlotWindow::AppendRequirementSignImage(const char * c_szImageName)
{
	for (TSlotListIterator itor = m_SlotList.begin(); itor != m_SlotList.end(); ++itor)
	{
		TSlot & rSlot = *itor;
		CImageBox *& rpSignImage = rSlot.pSignImage;

		if (!rpSignImage)
		{
			rpSignImage = new CImageBox(NULL);
			CWindowManager::Instance().SetParent(rpSignImage, this);
		}

		rpSignImage->LoadImage(c_szImageName);
		rpSignImage->Hide();
	}
}

BOOL CSlotWindow::HasSlot(DWORD dwIndex)
{
	TSlot * pSlot;
	if (!GetSlotPointer(dwIndex, &pSlot))
		return FALSE;

	return TRUE;
}

void CSlotWindow::SetSlot(DWORD dwIndex, DWORD dwVirtualNumber, BYTE byWidth, BYTE byHeight, CGraphicImage * pImage, D3DXCOLOR& diffuseColor)
{
	TSlot * pSlot;
	if (!GetSlotPointer(dwIndex, &pSlot))
		return;

	if (pSlot->isItem)
	if (pSlot->dwItemIndex == dwVirtualNumber)
	{
		pSlot->dwState = 0;
		pSlot->isItem = TRUE;
		if (pImage && pSlot->pInstance)
		{
			pSlot->pInstance->SetImagePointer(pImage);
		}
		return;
	}

	ClearSlot(pSlot);
	pSlot->dwState = 0;
	pSlot->isItem = TRUE;
	pSlot->dwItemIndex = dwVirtualNumber;

	if (pImage)
	{
		assert(NULL == pSlot->pInstance);
		pSlot->pInstance = CGraphicImageInstance::New();
		pSlot->pInstance->SetDiffuseColor(diffuseColor.r, diffuseColor.g, diffuseColor.b, diffuseColor.a);
		pSlot->pInstance->SetImagePointer(pImage);
	}

	pSlot->byxPlacedItemSize = byWidth;
	pSlot->byyPlacedItemSize = byHeight;

	if (pSlot->pCoverButton)
	{
		pSlot->pCoverButton->Show();
	}
}

#if defined(ENABLE_OKEY_CARD_GAME)
void CSlotWindow::SetCardSlot(uint32_t dwIndex, uint32_t dwVirtualNumber,
								uint8_t byWidth, uint8_t byHeight,
								const char* c_szFileName, D3DXCOLOR& diffuseColor)
{
	CGraphicImage * pImage = (CGraphicImage *)CResourceManager::Instance().GetResourcePointer(c_szFileName);
	TSlot * pSlot;
	if (!GetSlotPointer(dwIndex, &pSlot))
	{
		return;
	}

	if (pSlot->isItem)
	{
		if (pSlot->dwItemIndex == dwVirtualNumber)
		{
			pSlot->dwState = 0;
			pSlot->isItem = TRUE;
			if (pImage && pSlot->pInstance)
			{
				pSlot->pInstance->SetImagePointer(pImage);
			}

			return;
		}
	}

	ClearSlot(pSlot);
	pSlot->dwState = 0;
	pSlot->isItem = TRUE;
	pSlot->dwItemIndex = dwVirtualNumber;

	if (pImage)
	{
		assert(NULL == pSlot->pInstance);

		pSlot->pInstance = CGraphicImageInstance::New();
		pSlot->pInstance->SetImagePointer(pImage);
		pSlot->pInstance->SetDiffuseColor(diffuseColor.r, diffuseColor.g, diffuseColor.b, diffuseColor.a);
	}

	pSlot->byxPlacedItemSize = byWidth;
	pSlot->byyPlacedItemSize = byHeight;

	if (pSlot->pCoverButton)
	{
		pSlot->pCoverButton->Show();
	}
}
#endif

#ifdef NEW_PET_SYSTEM
void CSlotWindow::SetSlotScale(DWORD dwIndex, DWORD dwVirtualNumber, BYTE byWidth, BYTE byHeight, CGraphicImage * pImage, float sx, float sy, D3DXCOLOR& diffuseColor)
{
	TSlot * pSlot;
	if (!GetSlotPointer(dwIndex, &pSlot))
		return;

	if (pSlot->isItem)
		if (pSlot->dwItemIndex == dwVirtualNumber)
		{
			pSlot->dwState = 0;
			pSlot->isItem = TRUE;
			if (pImage && pSlot->pInstance)
			{
				pSlot->pInstance->SetImagePointer(pImage);
			}
			return;
		}

	ClearSlot(pSlot);
	pSlot->dwState = 0;
	pSlot->isItem = TRUE;
	pSlot->dwItemIndex = dwVirtualNumber;

	if (pImage)
	{
		assert(NULL == pSlot->pInstance);
		pSlot->pInstance = CGraphicImageInstance::New();
		pSlot->pInstance->SetDiffuseColor(diffuseColor.r, diffuseColor.g, diffuseColor.b, diffuseColor.a);
		pSlot->pInstance->SetImagePointer(pImage);
		pSlot->pInstance->SetScale(sx, sy);
	}

	pSlot->byxPlacedItemSize = byWidth;
	pSlot->byyPlacedItemSize = byHeight;

	if (pSlot->pCoverButton)
	{
		pSlot->pCoverButton->Show();
	}
}
#endif

void CSlotWindow::SetSlotCount(DWORD dwIndex, DWORD dwCount)
{
	TSlot * pSlot;
	if (!GetSlotPointer(dwIndex, &pSlot))
		return;

	if (dwCount <= 0)
	{
		if (pSlot->pNumberLine)
		{
			delete pSlot->pNumberLine;
			pSlot->pNumberLine = NULL;
		}
	}
	else
	{
		char szCount[16+1];
		_snprintf(szCount, sizeof(szCount), "%d", dwCount);

		if (!pSlot->pNumberLine)
		{
			CNumberLine * pNumberLine = new UI::CNumberLine(this);
			pNumberLine->SetHorizontalAlign(CNumberLine::HORIZONTAL_ALIGN_RIGHT);
			pNumberLine->Show();
			pSlot->pNumberLine = pNumberLine;
		}

		pSlot->pNumberLine->SetNumber(szCount);
	}
}

void CSlotWindow::SetSlotCountNew(DWORD dwIndex, DWORD dwGrade, DWORD dwCount)
{
	TSlot * pSlot;
	if (!GetSlotPointer(dwIndex, &pSlot))
		return;

	if (dwCount <= 0)
	{
		if (pSlot->pNumberLine)
		{
			delete pSlot->pNumberLine;
			pSlot->pNumberLine = NULL;
		}
	}
	else
	{
		char szCount[16+1];

		switch (dwGrade)
		{
			case 0:
				_snprintf(szCount, sizeof(szCount), "%d", dwCount);
				break;
			case 1:
				_snprintf(szCount, sizeof(szCount), "m%d", dwCount);
				break;
			case 2:
				_snprintf(szCount, sizeof(szCount), "g%d", dwCount);
				break;
			case 3:
				_snprintf(szCount, sizeof(szCount), "p");
				break;
		}

		if (!pSlot->pNumberLine)
		{
			CNumberLine * pNumberLine = new UI::CNumberLine(this);
			pNumberLine->SetHorizontalAlign(CNumberLine::HORIZONTAL_ALIGN_RIGHT);
			pNumberLine->Show();
			pSlot->pNumberLine = pNumberLine;
		}

		pSlot->pNumberLine->SetNumber(szCount);
	}
}

void CSlotWindow::SetSlotCoolTime(DWORD dwIndex, float fCoolTime, float fElapsedTime)
{
	TSlot * pSlot;
	if (!GetSlotPointer(dwIndex, &pSlot))
		return;

	pSlot->fCoolTime = fCoolTime;
	pSlot->fStartCoolTime = CTimer::Instance().GetCurrentSecond() - fElapsedTime;
}

void CSlotWindow::ActivateSlot(DWORD dwIndex)
{
	TSlot * pSlot;
	if (!GetSlotPointer(dwIndex, &pSlot))
	{
		return;
	}

	pSlot->bActive = true;
#if defined(ENABLE_HIGHLIGHT_SYSTEM)
	int32_t itemSize = pSlot->byyPlacedItemSize - 1;
	if (itemSize < 0)
	{
		itemSize = 1;
	}

	for (auto i = 0; i < pSlot->pNewSlotEffect.size(); i++)
	{
		auto& pSlotEffect = pSlot->pNewSlotEffect.at(i);
		if (pSlotEffect == nullptr)
		{
			char szBuf[128];
			pSlotEffect = std::make_shared<CAniImageBox>(nullptr);

			for (uint8_t j = 0; j < 13; j++)
			{
				if (i == 0)
				{
					snprintf(szBuf, sizeof(szBuf), "d:/ymir work/ui/public/slotactiveeffect/%02d.sub", j);
				}
				else
				{
					snprintf(szBuf, sizeof(szBuf), "d:/ymir work/ui/public/slotactiveeffect/slot%d/%02d.sub", (i + 1), j);
				}

				pSlotEffect->AppendImage(szBuf);
				pSlotEffect->SetRenderingMode(CGraphicExpandedImageInstance::RENDERING_MODE_SCREEN);
				pSlotEffect->SetDelay(2);
			}
		}

		if (i == (pSlot->byyPlacedItemSize - 1))
		{
			pSlotEffect->Show();
		}
		else
		{
			pSlotEffect->Hide();
		}
	}
#endif
}

void CSlotWindow::DeactivateSlot(DWORD dwIndex)
{
	TSlot * pSlot;
	if (!GetSlotPointer(dwIndex, &pSlot))
		return;

	pSlot->bActive = false;

#if defined(ENABLE_HIGHLIGHT_SYSTEM)
	for (const auto& pSlotEffect : pSlot->pNewSlotEffect)
	{
		if (pSlotEffect)
		{
			pSlotEffect->Hide();
		}
	}
#endif
}

void CSlotWindow::ClearSlot(DWORD dwIndex)
{
	TSlot* pSlot;
	if (!GetSlotPointer(dwIndex, &pSlot))
	{
		return;
	}

	ClearSlot(pSlot);
}

void CSlotWindow::ClearSlot(TSlot * pSlot)
{
	pSlot->bActive = FALSE;
	pSlot->byxPlacedItemSize = 1;
	pSlot->byyPlacedItemSize = 1;

	pSlot->isItem = FALSE;
	pSlot->dwState = 0;
	pSlot->fCoolTime = 0.0f;
	pSlot->fStartCoolTime = 0.0f;
	pSlot->dwCenterSlotNumber = 0xffffffff;

	pSlot->dwItemIndex = 0;
	pSlot->bRenderBaseSlotImage = true;

	if (pSlot->pInstance)
	{
		CGraphicImageInstance::Delete(pSlot->pInstance);
		pSlot->pInstance = NULL;
	}
	if (pSlot->pCoverButton)
	{
		pSlot->pCoverButton->Hide();
	}
	if (pSlot->pSlotButton)
	{
		pSlot->pSlotButton->Hide();
	}
	if (pSlot->pSignImage)
	{
 		pSlot->pSignImage->Hide();
	}
	if (pSlot->pFinishCoolTimeEffect)
	{
		pSlot->pFinishCoolTimeEffect->Hide();
	}

#if defined(ENABLE_HIGHLIGHT_SYSTEM)
	for (const auto& pSlotEffect : pSlot->pNewSlotEffect)
	{
		if (pSlotEffect)
		{
			pSlotEffect->Hide();
		}
	}
#endif
}

void CSlotWindow::ClearAllSlot()
{
	Destroy();
}

void CSlotWindow::RefreshSlot()
{
	OnRefreshSlot();

	// NOTE : Refresh ��E�ҡ� ToolTip ��� �ơ���A CO��I��U - [levites]
	if (IsRendering())
	{
		TSlot * pSlot;
		if (GetPickedSlotPointer(&pSlot))
		{
			OnOverOutItem();
			OnOverInItem(pSlot->dwSlotNumber);
		}
	}
}

void CSlotWindow::OnRefreshSlot()
{
}

#if defined(ENABLE_HIGHLIGHT_SYSTEM)
void CSlotWindow::SetSlotDiffuseColor(uint32_t index, D3DXCOLOR& diffusecolor)
{
	TSlot* pSlot;
	if (!GetSlotPointer(index, &pSlot))
	{
		return;
	}

	for (const auto& pSlotEffect : pSlot->pNewSlotEffect)
	{
		if (pSlotEffect)
		{
			pSlotEffect->SetDiffuseColor(diffusecolor.r, diffusecolor.g, diffusecolor.b, diffusecolor.a);
		}
	}
}
#endif

DWORD CSlotWindow::GetSlotCount()
{
	return m_SlotList.size();
}

void CSlotWindow::LockSlot(DWORD dwIndex)
{
	TSlot * pSlot;
	if (!GetSlotPointer(dwIndex, &pSlot))
		return;

	pSlot->dwState |= SLOT_STATE_LOCK;
}
void CSlotWindow::UnlockSlot(DWORD dwIndex)
{
	TSlot * pSlot;
	if (!GetSlotPointer(dwIndex, &pSlot))
		return;

	pSlot->dwState ^= SLOT_STATE_LOCK;
}
void CSlotWindow::SetCantUseSlot(DWORD dwIndex)
{
	TSlot * pSlot;
	if (!GetSlotPointer(dwIndex, &pSlot))
		return;

	pSlot->dwState |= SLOT_STATE_CANT_USE;
}
void CSlotWindow::SetUseSlot(DWORD dwIndex)
{
	TSlot * pSlot;
	if (!GetSlotPointer(dwIndex, &pSlot))
		return;

	pSlot->dwState ^= SLOT_STATE_CANT_USE;
}

#if defined(ENABLE_SLOT_COVER_TRAFFIC_LIGHTS)
void CSlotWindow::SetSlotTrafficLight(DWORD dwIndex, BYTE yLight)
{
	TSlot* pSlot;
	if (!GetSlotPointer(dwIndex, &pSlot))
		return;

	switch (yLight)
	{
	case SLOT_TRAFFIC_LIGHT_RED:
		SET_BIT(pSlot->dwState, SLOT_STATE_TRAFFIC_LIGHT_RED);
		DisableSlotTrafficLight(dwIndex, SLOT_TRAFFIC_LIGHT_YELLOW);
		DisableSlotTrafficLight(dwIndex, SLOT_TRAFFIC_LIGHT_GREEN);
		break;

	case SLOT_TRAFFIC_LIGHT_YELLOW:
		DisableSlotTrafficLight(dwIndex, SLOT_TRAFFIC_LIGHT_RED);
		SET_BIT(pSlot->dwState, SLOT_STATE_TRAFFIC_LIGHT_YELLOW);
		DisableSlotTrafficLight(dwIndex, SLOT_TRAFFIC_LIGHT_GREEN);
		break;

	case SLOT_TRAFFIC_LIGHT_GREEN:
		DisableSlotTrafficLight(dwIndex, SLOT_TRAFFIC_LIGHT_RED);
		DisableSlotTrafficLight(dwIndex, SLOT_TRAFFIC_LIGHT_YELLOW);
		SET_BIT(pSlot->dwState, SLOT_STATE_TRAFFIC_LIGHT_GREEN);
		break;

	default:
		return;
	}
}

void CSlotWindow::DisableSlotTrafficLight(DWORD dwIndex, BYTE yLight)
{
	TSlot* pSlot;
	if (!GetSlotPointer(dwIndex, &pSlot))
		return;

	switch (yLight)
	{
	case SLOT_TRAFFIC_LIGHT_RED:
		REMOVE_BIT(pSlot->dwState, SLOT_STATE_TRAFFIC_LIGHT_RED);
		break;
	case SLOT_TRAFFIC_LIGHT_YELLOW:
		REMOVE_BIT(pSlot->dwState, SLOT_STATE_TRAFFIC_LIGHT_YELLOW);
		break;
	case SLOT_TRAFFIC_LIGHT_GREEN:
		REMOVE_BIT(pSlot->dwState, SLOT_STATE_TRAFFIC_LIGHT_GREEN);
		break;
	default:
		REMOVE_BIT(pSlot->dwState, SLOT_STATE_TRAFFIC_LIGHT_RED);
		REMOVE_BIT(pSlot->dwState, SLOT_STATE_TRAFFIC_LIGHT_YELLOW);
		REMOVE_BIT(pSlot->dwState, SLOT_STATE_TRAFFIC_LIGHT_GREEN);
		return;
	}
}
#endif

void CSlotWindow::EnableSlot(DWORD dwIndex)
{
	TSlot * pSlot;
	if (!GetSlotPointer(dwIndex, &pSlot))
		return;

	REMOVE_BIT(pSlot->dwState, SLOT_STATE_DISABLE);
	//pSlot->dwState |= SLOT_STATE_DISABLE;
}
void CSlotWindow::DisableSlot(DWORD dwIndex)
{
	TSlot * pSlot;
	if (!GetSlotPointer(dwIndex, &pSlot))
		return;
	SET_BIT(pSlot->dwState, SLOT_STATE_DISABLE);
	//pSlot->dwState ^= SLOT_STATE_DISABLE;
}

// Select

void CSlotWindow::SelectSlot(DWORD dwSelectingIndex)
{
	std::list<DWORD>::iterator itor = m_dwSelectedSlotIndexList.begin();
	for (; itor != m_dwSelectedSlotIndexList.end();)
	{
		if (dwSelectingIndex == *itor)
		{
			itor = m_dwSelectedSlotIndexList.erase(itor);
			return;
		}
		else
		{
			++itor;
		}
	}

	TSlot * pSlot;
	if (GetSlotPointer(dwSelectingIndex, &pSlot))
	{
		if (!pSlot->isItem)
			return;

		m_dwSelectedSlotIndexList.push_back(dwSelectingIndex);
	}
}

BOOL CSlotWindow::isSelectedSlot(DWORD dwIndex)
{
	std::list<DWORD>::iterator itor = m_dwSelectedSlotIndexList.begin();
	for (; itor != m_dwSelectedSlotIndexList.end(); ++itor)
	{
		if (dwIndex == *itor)
			return TRUE;
	}

	return FALSE;
}

void CSlotWindow::ClearSelected()
{
	m_dwSelectedSlotIndexList.clear();
}

DWORD CSlotWindow::GetSelectedSlotCount()
{
	return m_dwSelectedSlotIndexList.size();
}

DWORD CSlotWindow::GetSelectedSlotNumber(DWORD dwIndex)
{
	if (dwIndex >= m_dwSelectedSlotIndexList.size())
		return DWORD(-1);

	DWORD dwCount = 0;
	std::list<DWORD>::iterator itor = m_dwSelectedSlotIndexList.begin();
	for (; itor != m_dwSelectedSlotIndexList.end(); ++itor)
	{
		if (dwIndex == dwCount)
			break;

		++dwCount;
	}

	return *itor;
}

void CSlotWindow::ShowSlotButton(DWORD dwSlotNumber)
{
	TSlot * pSlot;
	if (!GetSlotPointer(dwSlotNumber, &pSlot))
		return;

	if (pSlot->pSlotButton)
	{
		pSlot->pSlotButton->Show();
	}
}

void CSlotWindow::HideAllSlotButton()
{
	for (TSlotListIterator itor = m_SlotList.begin(); itor != m_SlotList.end(); ++itor)
	{
		TSlot & rSlot = *itor;

		if (rSlot.pSlotButton)
		{
			rSlot.pSlotButton->Hide();
		}
	}
}

void CSlotWindow::ShowRequirementSign(DWORD dwSlotNumber)
{
	TSlot * pSlot;
	if (!GetSlotPointer(dwSlotNumber, &pSlot))
		return;

	if (!pSlot->pSignImage)
		return;

	pSlot->pSignImage->Show();
}

void CSlotWindow::HideRequirementSign(DWORD dwSlotNumber)
{
	TSlot * pSlot;
	if (!GetSlotPointer(dwSlotNumber, &pSlot))
		return;

	if (!pSlot->pSignImage)
		return;

	pSlot->pSignImage->Hide();
}

// Event

BOOL CSlotWindow::OnMouseLeftButtonDown()
{
	TSlot * pSlot;
	if (!GetPickedSlotPointer(&pSlot))
	{
		UI::CWindowManager::Instance().DeattachIcon();
		return TRUE;
	}

#ifdef WJ_ENABLE_TRADABLE_ICON
	if (!(pSlot->dwState & SLOT_STATE_CANT_MOUSE_EVENT)) {
		if (pSlot->isItem && !(pSlot->dwState & SLOT_STATE_LOCK))
			OnSelectItemSlot(pSlot->dwSlotNumber);
		else
			OnSelectEmptySlot(pSlot->dwSlotNumber);
	}
#else
	if (pSlot->isItem && !(pSlot->dwState & SLOT_STATE_LOCK))
	{
		OnSelectItemSlot(pSlot->dwSlotNumber);
	}
	else
	{
		OnSelectEmptySlot(pSlot->dwSlotNumber);
	}
#endif

	return TRUE;
}

BOOL CSlotWindow::OnMouseLeftButtonUp()
{
	if (UI::CWindowManager::Instance().IsAttaching())
	if (UI::CWindowManager::Instance().IsDragging())
	if (IsIn())
	{
		UI::CWindow * pWin = UI::CWindowManager::Instance().GetPointWindow();

		if (pWin)
		if (pWin->IsType(UI::CSlotWindow::Type()))
		{
			UI::CSlotWindow * pSlotWin = (UI::CSlotWindow *)pWin;

			TSlot * pSlot;
			if (!pSlotWin->GetPickedSlotPointer(&pSlot))
			{
				UI::CWindowManager::Instance().DeattachIcon();
				return TRUE;
			}

#ifdef WJ_ENABLE_TRADABLE_ICON
			if (!(pSlot->dwState & SLOT_STATE_CANT_MOUSE_EVENT)) {
				if (pSlot->isItem)
					pSlotWin->OnSelectItemSlot(pSlot->dwSlotNumber);
				else
					pSlotWin->OnSelectEmptySlot(pSlot->dwSlotNumber);
			}
#else
			if (pSlot->isItem)
				pSlotWin->OnSelectItemSlot(pSlot->dwSlotNumber);
			else
				pSlotWin->OnSelectEmptySlot(pSlot->dwSlotNumber);
#endif

			return TRUE;
		}

		return FALSE;
	}

	return FALSE;
}

BOOL CSlotWindow::OnMouseRightButtonDown()
{
	TSlot * pSlot;
	if (!GetPickedSlotPointer(&pSlot))
		return TRUE;

#ifdef WJ_ENABLE_TRADABLE_ICON
	if (!(pSlot->dwState & SLOT_STATE_CANT_MOUSE_EVENT)) {
		if (pSlot->isItem)
			OnUnselectItemSlot(pSlot->dwSlotNumber);
		else
			OnUnselectEmptySlot(pSlot->dwSlotNumber);
	}
#else
	if (pSlot->isItem)
		OnUnselectItemSlot(pSlot->dwSlotNumber);
	else
		OnUnselectEmptySlot(pSlot->dwSlotNumber);
#endif

	return TRUE;
}

BOOL CSlotWindow::OnMouseLeftButtonDoubleClick()
{
	TSlot * pSlot;
#ifdef WJ_ENABLE_TRADABLE_ICON
	if (GetPickedSlotPointer(&pSlot))
		if (!(pSlot->dwState & SLOT_STATE_CANT_MOUSE_EVENT))
			OnUseSlot();
#else
	if (GetPickedSlotPointer(&pSlot))
		OnUseSlot();
#endif

	return TRUE;
}

void CSlotWindow::OnMouseOverOut()
{
	OnOverOutItem();
}

void CSlotWindow::OnMouseOver()
{
	// FIXME : A�ϥ�좯i��| ��a������e CI��A ���A������ SetTopAI ��C��i��o���碬e Capture�Ƣ� C���iA�� ��o���Ƣ�U. ������IAC ����Ao AU��a.
	//         A�� ��o ��U����AuAI C����aA��A�� A�̨������� CO ��i - [levites]
//	if (UI::CWindowManager::Instance().IsCapture())
//	if (!UI::CWindowManager::Instance().IsAttaching())
//		return;

	CWindow * pPointWindow = UI::CWindowManager::Instance().GetPointWindow();
	if (this == pPointWindow)
	{
		TSlot * pSlot;
		if (GetPickedSlotPointer(&pSlot))
		{
			if (pSlot->isItem)
			{
				if (OnOverInItem(pSlot->dwSlotNumber))
					return;
			}
			else
			{
				if (OnOverInEmptySlot(pSlot->dwSlotNumber))
					return;
			}
		}
	}

	OnOverOutItem();
	OnOverOutEmptySlot();
}

void CSlotWindow::OnSelectEmptySlot(int iSlotNumber)
{
	PyCallClassMemberFunc(m_poHandler, "OnSelectEmptySlot", Py_BuildValue("(i)", iSlotNumber));
}
void CSlotWindow::OnSelectItemSlot(int iSlotNumber)
{
//	OnOverOutItem();
	PyCallClassMemberFunc(m_poHandler, "OnSelectItemSlot", Py_BuildValue("(i)", iSlotNumber));

	if (UI::CWindowManager::Instance().IsAttaching())
		OnOverOutItem();
}
void CSlotWindow::OnUnselectEmptySlot(int iSlotNumber)
{
	PyCallClassMemberFunc(m_poHandler, "OnUnselectEmptySlot", Py_BuildValue("(i)", iSlotNumber));
}
void CSlotWindow::OnUnselectItemSlot(int iSlotNumber)
{
	PyCallClassMemberFunc(m_poHandler, "OnUnselectItemSlot", Py_BuildValue("(i)", iSlotNumber));
}
void CSlotWindow::OnUseSlot()
{
	TSlot * pSlot;
	if (GetPickedSlotPointer(&pSlot))
	if (pSlot->isItem)
	{
		PyCallClassMemberFunc(m_poHandler, "OnUseSlot", Py_BuildValue("(i)", pSlot->dwSlotNumber));
	}
}

BOOL CSlotWindow::OnOverInItem(DWORD dwSlotNumber)
{
	TSlot * pSlot;
	if (!GetSlotPointer(dwSlotNumber, &pSlot))
		return FALSE;

	if (!pSlot->isItem)
		return FALSE;

	if (pSlot->dwSlotNumber == m_dwToolTipSlotNumber)
		return TRUE;

	m_dwToolTipSlotNumber = dwSlotNumber;
	PyCallClassMemberFunc(m_poHandler, "OnOverInItem", Py_BuildValue("(i)", dwSlotNumber));

	return TRUE;
}

BOOL CSlotWindow::OnOverInEmptySlot(DWORD dwSlotNumber)
{
	TSlot * pSlot;
	if (!GetSlotPointer(dwSlotNumber, &pSlot))
		return FALSE;

	if (pSlot->dwSlotNumber == m_dwToolTipSlotNumber)
		return TRUE;

	m_dwToolTipSlotNumber = dwSlotNumber;
	PyCallClassMemberFunc(m_poHandler, "OnOverInEmptySlot", Py_BuildValue("(i)", dwSlotNumber));

	return TRUE;
}

void CSlotWindow::OnOverOutItem()
{
	if (SLOT_NUMBER_NONE == m_dwToolTipSlotNumber)
		return;

	m_dwToolTipSlotNumber = SLOT_NUMBER_NONE;
	PyCallClassMemberFunc(m_poHandler, "OnOverOutItem", Py_BuildValue("()"));
}

void CSlotWindow::OnOverOutEmptySlot()
{
	if (SLOT_NUMBER_NONE == m_dwToolTipSlotNumber)
		return;

	m_dwToolTipSlotNumber = SLOT_NUMBER_NONE;
	PyCallClassMemberFunc(m_poHandler, "OnOverOutEmptySlot", Py_BuildValue("()"));
}

void CSlotWindow::OnPressedSlotButton(DWORD dwType, DWORD dwSlotNumber, BOOL isLeft)
{
	if (CSlotButton::SLOT_BUTTON_TYPE_PLUS == dwType)
	{
		PyCallClassMemberFunc(m_poHandler, "OnPressedSlotButton", Py_BuildValue("(i)", dwSlotNumber));
	}
	else if (CSlotButton::SLOT_BUTTON_TYPE_COVER == dwType)
	{
		if (isLeft)
		{
			OnMouseLeftButtonDown();
		}
	}
}

void CSlotWindow::OnUpdate()
{
	for (std::deque<DWORD>::iterator itor = m_ReserveDestroyEffectDeque.begin(); itor != m_ReserveDestroyEffectDeque.end(); ++itor)
	{
		DWORD dwSlotIndex = *itor;

		TSlot * pSlot;
		if (!GetSlotPointer(dwSlotIndex, &pSlot))
			continue;

		__DestroyFinishCoolTimeEffect(pSlot);
	}

	m_ReserveDestroyEffectDeque.clear();
}

void CSlotWindow::OnRender()
{
	RenderSlotBaseImage();

	switch (m_dwSlotStyle)
	{
		case SLOT_STYLE_PICK_UP:
			OnRenderPickingSlot();
			break;
		case SLOT_STYLE_SELECT:
			OnRenderSelectedSlot();
			break;
	}

	std::for_each(m_pChildList.begin(), m_pChildList.end(), std::mem_fn(&CWindow::OnRender));

	TSlotListIterator itor;

	//
	// ������c ������O ��oAU �������硾a
	//////////////////////////////////////////////////////////////////////////
#ifdef __RENDER_SLOT_AREA__
	CPythonGraphic::Instance().SetDiffuseColor(0.5f, 0.5f, 0.5f);
	for (itor = m_SlotList.begin(); itor != m_SlotList.end(); ++itor)
	{
		TSlot & rSlot = *itor;
		CPythonGraphic::Instance().RenderBox2d(m_rect.left + rSlot.ixPosition,
											   m_rect.top + rSlot.iyPosition,
											   m_rect.left + rSlot.ixPosition + rSlot.ixCellSize,
											   m_rect.top + rSlot.iyPosition + rSlot.iyCellSize);
	}
	CPythonGraphic::Instance().SetDiffuseColor(1.0f, 0.0f, 0.0f, 1.0f);
	CPythonGraphic::Instance().RenderBox2d(m_rect.left, m_rect.top, m_rect.right, m_rect.bottom);
#endif
	//////////////////////////////////////////////////////////////////////////

	for (itor = m_SlotList.begin(); itor != m_SlotList.end(); ++itor)
	{
		TSlot & rSlot = *itor;

		if (rSlot.pSlotButton)
		{
			rSlot.pSlotButton->SetPosition(rSlot.ixPosition + 1, rSlot.iyPosition + 19);
		}

		if (rSlot.pSignImage)
		{
			rSlot.pSignImage->SetPosition(rSlot.ixPosition - 7, rSlot.iyPosition + 10);
		}

		if (rSlot.pInstance)
		{
			rSlot.pInstance->SetPosition(m_rect.left + rSlot.ixPosition, m_rect.top + rSlot.iyPosition);
			rSlot.pInstance->Render();
		}

		if (!rSlot.isItem)
		{
			if (IS_SET(rSlot.dwState, SLOT_STATE_ALWAYS_RENDER_COVER))
			{
				rSlot.pCoverButton->Show();
				rSlot.pCoverButton->SetPosition(rSlot.ixPosition, rSlot.iyPosition);
				rSlot.pCoverButton->RenderButton();
			}

			continue;
		}

		if (IS_SET(rSlot.dwState, SLOT_STATE_DISABLE))
		{
			CPythonGraphic::Instance().SetDiffuseColor(1.0f, 0.0f, 0.0f, 0.3f);
			CPythonGraphic::Instance().RenderBar2d(m_rect.left + rSlot.ixPosition,
				m_rect.top + rSlot.iyPosition,
				m_rect.left + rSlot.ixPosition + rSlot.ixCellSize,
				m_rect.top + rSlot.iyPosition + rSlot.iyCellSize);
		}

#ifdef WJ_ENABLE_TRADABLE_ICON
		if (IS_SET(rSlot.dwState, SLOT_STATE_CANT_MOUSE_EVENT))
		{
			CPythonGraphic::Instance().SetDiffuseColor(1.0f, 0.0f, 0.0f, 0.3f);
			CPythonGraphic::Instance().RenderBar2d(m_rect.left + rSlot.ixPosition,
				m_rect.top + rSlot.iyPosition,
				m_rect.left + rSlot.ixPosition + rSlot.byxPlacedItemSize * ITEM_WIDTH,
				m_rect.top + rSlot.iyPosition + rSlot.byyPlacedItemSize * ITEM_HEIGHT);
		}

		if (IS_SET(rSlot.dwState, SLOT_STATE_UNUSABLE))
		{
			CPythonGraphic::Instance().SetDiffuseColor(1.0f, 1.0f, 1.0f, 0.3f);
			CPythonGraphic::Instance().RenderBar2d(m_rect.left + rSlot.ixPosition,
				m_rect.top + rSlot.iyPosition,
				m_rect.left + rSlot.ixPosition + rSlot.byxPlacedItemSize * ITEM_WIDTH,
				m_rect.top + rSlot.iyPosition + rSlot.byyPlacedItemSize * ITEM_HEIGHT);
		}
#endif

#if defined(ENABLE_SLOT_COVER_TRAFFIC_LIGHTS)
		if (IS_SET(rSlot.dwState, SLOT_STATE_TRAFFIC_LIGHT_RED))
		{
			CPythonGraphic::Instance().SetDiffuseColor(1.0f, 74.0f / 255.0f, 74.0f / 255.0f, 0.3f);
			CPythonGraphic::Instance().RenderBar2d(m_rect.left + rSlot.ixPosition,
				m_rect.top + rSlot.iyPosition,
				m_rect.left + rSlot.ixPosition + rSlot.byxPlacedItemSize * rSlot.ixCellSize,
				m_rect.top + rSlot.iyPosition + rSlot.byyPlacedItemSize * rSlot.iyCellSize);
		}

		if (IS_SET(rSlot.dwState, SLOT_STATE_TRAFFIC_LIGHT_YELLOW))
		{
			CPythonGraphic::Instance().SetDiffuseColor(1.0f, 1.0f, 74.0f / 255.0f, 0.3f);
			CPythonGraphic::Instance().RenderBar2d(m_rect.left + rSlot.ixPosition,
				m_rect.top + rSlot.iyPosition,
				m_rect.left + rSlot.ixPosition + rSlot.byxPlacedItemSize * rSlot.ixCellSize,
				m_rect.top + rSlot.iyPosition + rSlot.byyPlacedItemSize * rSlot.iyCellSize);
		}

		if (IS_SET(rSlot.dwState, SLOT_STATE_TRAFFIC_LIGHT_GREEN))
		{
			CPythonGraphic::Instance().SetDiffuseColor(74.0f / 255.0f, 1.0f, 74.0f / 255.0f, 0.3f);
			CPythonGraphic::Instance().RenderBar2d(m_rect.left + rSlot.ixPosition,
				m_rect.top + rSlot.iyPosition,
				m_rect.left + rSlot.ixPosition + rSlot.byxPlacedItemSize * rSlot.ixCellSize,
				m_rect.top + rSlot.iyPosition + rSlot.byyPlacedItemSize * rSlot.iyCellSize);
		}
#endif

		if (rSlot.fCoolTime != 0.0f)
		{
			float fcurTime = CTimer::Instance().GetCurrentSecond();
			float fPercentage = (fcurTime - rSlot.fStartCoolTime) / rSlot.fCoolTime;
			CPythonGraphic::Instance().RenderCoolTimeBox(m_rect.left + rSlot.ixPosition + 16.0f, m_rect.top + rSlot.iyPosition + 16.0f, 16.0f, fPercentage);

			if (fcurTime - rSlot.fStartCoolTime >= rSlot.fCoolTime)
			{
				if ((fcurTime - rSlot.fStartCoolTime) - rSlot.fCoolTime < 1.0f)
					__CreateFinishCoolTimeEffect(&rSlot);

				rSlot.fCoolTime = 0.0f;
				rSlot.fStartCoolTime = 0.0f;
			}
		}

		if (rSlot.pCoverButton)
		{
			rSlot.pCoverButton->SetPosition(rSlot.ixPosition, rSlot.iyPosition);
			rSlot.pCoverButton->RenderButton();
		}

		if (rSlot.pNumberLine) {
			int ix = rSlot.byxPlacedItemSize*ITEM_WIDTH + rSlot.ixPosition - 4;
			int iy = rSlot.iyPosition + rSlot.byyPlacedItemSize*ITEM_HEIGHT - 12 + 2;

			rSlot.pNumberLine->SetPosition(ix, iy);
			rSlot.pNumberLine->Update();
			rSlot.pNumberLine->Render();
		}

		if (rSlot.pFinishCoolTimeEffect) {
			rSlot.pFinishCoolTimeEffect->SetPosition(rSlot.ixPosition, rSlot.iyPosition);
			rSlot.pFinishCoolTimeEffect->Update();
			rSlot.pFinishCoolTimeEffect->Render();
		}

#if defined(ENABLE_HIGHLIGHT_SYSTEM)
		for (const auto& pSlotEffect : rSlot.pNewSlotEffect)
		{
			if (!pSlotEffect 
				|| pSlotEffect->IsShow() == false)
			{
				continue;
			}

			pSlotEffect->SetPosition(m_rect.left + rSlot.ixPosition, m_rect.top + rSlot.iyPosition);
			pSlotEffect->Update();
			pSlotEffect->Render();
		}
#endif
	}

	RenderLockedSlot();
}

void CSlotWindow::RenderSlotBaseImage()
{
	if (!m_pBaseImageInstance)
		return;

	for (TSlotListIterator itor = m_SlotList.begin(); itor != m_SlotList.end(); ++itor)
	{
		TSlot & rSlot = *itor;

		if (!rSlot.bRenderBaseSlotImage)
			continue;

		m_pBaseImageInstance->SetPosition(m_rect.left + rSlot.ixPosition, m_rect.top + rSlot.iyPosition);
		m_pBaseImageInstance->Render();
	}
}

void CSlotWindow::OnRenderPickingSlot()
{
	if (!UI::CWindowManager::Instance().IsAttaching())
		return;

	TSlot * pSlot;
	if (!GetSelectedSlotPointer(&pSlot))
		return;

	CPythonGraphic::Instance().SetDiffuseColor(1.0f, 1.0f, 1.0f, 0.5f);

	CPythonGraphic::Instance().RenderBar2d(m_rect.left + pSlot->ixPosition,
											m_rect.top + pSlot->iyPosition,
											m_rect.left + pSlot->ixPosition + pSlot->ixCellSize,
											m_rect.top + pSlot->iyPosition + pSlot->iyCellSize);
}

void CSlotWindow::OnRenderSelectedSlot()
{
	std::list<DWORD>::iterator itor = m_dwSelectedSlotIndexList.begin();
	for (; itor != m_dwSelectedSlotIndexList.end(); ++itor)
	{
		TSlot * pSlot;
		if (!GetSlotPointer(*itor, &pSlot))
			continue;

		CPythonGraphic::Instance().SetDiffuseColor(1.0f, 1.0f, 1.0f, 0.5f);
		CPythonGraphic::Instance().RenderBar2d(m_rect.left + pSlot->ixPosition,
												m_rect.top + pSlot->iyPosition,
												m_rect.left + pSlot->ixPosition + pSlot->ixCellSize,
												m_rect.top + pSlot->iyPosition + pSlot->iyCellSize);
	}
}

void CSlotWindow::RenderLockedSlot()
{
	CPythonGraphic::Instance().SetDiffuseColor(0.0f, 0.0f, 0.0f, 0.5f);
	for (TSlotListIterator itor = m_SlotList.begin(); itor != m_SlotList.end(); ++itor)
	{
		TSlot & rSlot = *itor;

		if (!rSlot.isItem)
			continue;

		if (rSlot.dwState & SLOT_STATE_LOCK)
		{
			CPythonGraphic::Instance().RenderBar2d(m_rect.left + rSlot.ixPosition,
												   m_rect.top  + rSlot.iyPosition,
												   m_rect.left + rSlot.ixPosition + rSlot.ixCellSize,
												   m_rect.top  + rSlot.iyPosition + rSlot.iyCellSize);
		}
	}
}

// Check Slot

BOOL CSlotWindow::GetSlotPointer(DWORD dwIndex, TSlot ** ppSlot)
{
	for (TSlotListIterator itor = m_SlotList.begin(); itor != m_SlotList.end(); ++itor)
	{
		TSlot & rSlot = *itor;

		if (dwIndex == rSlot.dwSlotNumber)
		{
			*ppSlot = &rSlot;
			return TRUE;
		}
	}

	return FALSE;
}

BOOL CSlotWindow::GetSelectedSlotPointer(TSlot ** ppSlot)
{
	long lx, ly;
	GetMouseLocalPosition(lx, ly);

	for (TSlotListIterator itor = m_SlotList.begin(); itor != m_SlotList.end(); ++itor)
	{
		TSlot & rSlot = *itor;

		if (lx >= rSlot.ixPosition)
		if (ly >= rSlot.iyPosition)
		if (lx <= rSlot.ixPosition + rSlot.ixCellSize)
		if (ly <= rSlot.iyPosition + rSlot.iyCellSize)
		{
			*ppSlot = &rSlot;
			return TRUE;
		}
	}

	return FALSE;
}

BOOL CSlotWindow::GetPickedSlotPointer(TSlot ** ppSlot)
{
	long lx, ly;
	CWindowManager::Instance().GetMousePosition(lx, ly);

	int ixLocal = lx - m_rect.left;
	int iyLocal = ly - m_rect.top;

	// NOTE : ����AE ��CA�� ��o��U CN�ơ�AI ��aA�� AI��o��A A��A�� AI��eC�� ����AE A�ע���������IAI ��A����AE ����������I
	//        A����E��I ��E��oC�� �ơ�A����I��a �좴Co AO��A SlotA�� AU�좯 �����A ��E��U��A ��?����A�� AI��eCN��U. - [levites]
	for (TSlotListIterator itor = m_SlotList.begin(); itor != m_SlotList.end(); ++itor)
	{
		TSlot & rSlot = *itor;

		int ixCellSize = rSlot.ixCellSize;
		int iyCellSize = rSlot.iyCellSize;

		// NOTE : ItemAI Hide ��C��iAOA�� �Ʃ���i��| A��CN..
		if (rSlot.isItem)
		{
			ixCellSize = max(rSlot.ixCellSize, int(rSlot.byxPlacedItemSize * ITEM_WIDTH));
			iyCellSize = max(rSlot.iyCellSize, int(rSlot.byyPlacedItemSize * ITEM_HEIGHT));
		}

		if (ixLocal >= rSlot.ixPosition)
		if (iyLocal >= rSlot.iyPosition)
		if (ixLocal <= rSlot.ixPosition + ixCellSize)
		if (iyLocal <= rSlot.iyPosition + iyCellSize)
		{
			*ppSlot = &rSlot;
			return TRUE;
		}
	}

	return FALSE;
}

void CSlotWindow::SetUseMode(BOOL bFlag)
{
	m_isUseMode = bFlag;
}

void CSlotWindow::SetUsableItem(BOOL bFlag)
{
	m_isUsableItem = bFlag;
}

void CSlotWindow::ReserveDestroyCoolTimeFinishEffect(DWORD dwSlotIndex)
{
	m_ReserveDestroyEffectDeque.push_back(dwSlotIndex);
}

DWORD CSlotWindow::Type()
{
	static int s_Type = GetCRC32("CSlotWindow", strlen("CSlotWindow"));
	return s_Type;
}

BOOL CSlotWindow::OnIsType(DWORD dwType)
{
	if (CSlotWindow::Type() == dwType)
		return TRUE;

	return CWindow::OnIsType(dwType);
}

void CSlotWindow::__CreateToggleSlotImage()
{
	__DestroyToggleSlotImage();

	m_pToggleSlotImage = new CImageBox(NULL);
	m_pToggleSlotImage->LoadImage("d:/ymir work/ui/public/slot_toggle.sub");
	m_pToggleSlotImage->Show();
}

void CSlotWindow::__CreateFinishCoolTimeEffect(TSlot * pSlot)
{
	__DestroyFinishCoolTimeEffect(pSlot);

	CAniImageBox * pFinishCoolTimeEffect = new CCoolTimeFinishEffect(this, pSlot->dwSlotNumber);
	pFinishCoolTimeEffect->AppendImage("d:/ymir work/ui/public/slotfinishcooltimeeffect/00.sub");
	pFinishCoolTimeEffect->AppendImage("d:/ymir work/ui/public/slotfinishcooltimeeffect/01.sub");
	pFinishCoolTimeEffect->AppendImage("d:/ymir work/ui/public/slotfinishcooltimeeffect/02.sub");
	pFinishCoolTimeEffect->AppendImage("d:/ymir work/ui/public/slotfinishcooltimeeffect/03.sub");
	pFinishCoolTimeEffect->AppendImage("d:/ymir work/ui/public/slotfinishcooltimeeffect/04.sub");
	pFinishCoolTimeEffect->AppendImage("d:/ymir work/ui/public/slotfinishcooltimeeffect/05.sub");
	pFinishCoolTimeEffect->AppendImage("d:/ymir work/ui/public/slotfinishcooltimeeffect/06.sub");
	pFinishCoolTimeEffect->AppendImage("d:/ymir work/ui/public/slotfinishcooltimeeffect/07.sub");
	pFinishCoolTimeEffect->AppendImage("d:/ymir work/ui/public/slotfinishcooltimeeffect/08.sub");
	pFinishCoolTimeEffect->AppendImage("d:/ymir work/ui/public/slotfinishcooltimeeffect/09.sub");
	pFinishCoolTimeEffect->AppendImage("d:/ymir work/ui/public/slotfinishcooltimeeffect/10.sub");
	pFinishCoolTimeEffect->SetRenderingMode(CGraphicExpandedImageInstance::RENDERING_MODE_SCREEN);
	pFinishCoolTimeEffect->ResetFrame();
	pFinishCoolTimeEffect->SetDelay(2);
	pFinishCoolTimeEffect->Show();

	pSlot->pFinishCoolTimeEffect = pFinishCoolTimeEffect;
}

void CSlotWindow::__CreateBaseImage(const char * c_szFileName, float fr, float fg, float fb, float fa)
{
	__DestroyBaseImage();

	CGraphicImage * pImage = (CGraphicImage *)CResourceManager::Instance().GetResourcePointer(c_szFileName);
	m_pBaseImageInstance = CGraphicImageInstance::New();
	m_pBaseImageInstance->SetImagePointer(pImage);
	m_pBaseImageInstance->SetDiffuseColor(fr, fg, fb, fa);
}

#ifdef NEW_PET_SYSTEM
void CSlotWindow::__CreateBaseImageScale(const char * c_szFileName, float fr, float fg, float fb, float fa, float sx, float sy)
{
	__DestroyBaseImage();

	CGraphicImage * pImage = (CGraphicImage *)CResourceManager::Instance().GetResourcePointer(c_szFileName);
	m_pBaseImageInstance = CGraphicImageInstance::New();
	m_pBaseImageInstance->SetImagePointer(pImage);
	m_pBaseImageInstance->SetDiffuseColor(fr, fg, fb, fa);
	m_pBaseImageInstance->SetScale(sx, sy);
}
#endif

void CSlotWindow::__DestroyToggleSlotImage()
{
	if (m_pToggleSlotImage)
	{
		delete m_pToggleSlotImage;
		m_pToggleSlotImage = NULL;
	}
}

void CSlotWindow::__DestroyFinishCoolTimeEffect(TSlot * pSlot)
{
	if (pSlot->pFinishCoolTimeEffect)
	{
		delete pSlot->pFinishCoolTimeEffect;
		pSlot->pFinishCoolTimeEffect = NULL;
	}
}

void CSlotWindow::__DestroyBaseImage()
{
	if (m_pBaseImageInstance)
	{
		CGraphicImageInstance::Delete(m_pBaseImageInstance);
		m_pBaseImageInstance = NULL;
	}
}

void CSlotWindow::__Initialize()
{
	m_dwSlotType = 0;
	m_dwSlotStyle = SLOT_STYLE_PICK_UP;
	m_dwToolTipSlotNumber = SLOT_NUMBER_NONE;

	m_isUseMode = FALSE;
	m_isUsableItem = FALSE;

	m_pToggleSlotImage = NULL;
	m_pBaseImageInstance = NULL;

#if defined(ENABLE_OFFLINESHOP_REWORK)
	if (m_pGrid)
	{
		m_pGrid.release();
		m_pGrid = nullptr;
	}
#endif
}

void CSlotWindow::Destroy()
{
	for (TSlotListIterator itor = m_SlotList.begin(); itor != m_SlotList.end(); ++itor)
	{
		TSlot & rSlot = *itor;

		ClearSlot(&rSlot);

		if (rSlot.pNumberLine)
		{
			delete rSlot.pNumberLine;
			rSlot.pNumberLine = NULL;
		}
		if (rSlot.pCoverButton)
		{
			CWindowManager::Instance().DestroyWindow(rSlot.pCoverButton);
		}
		if (rSlot.pSlotButton)
		{
			CWindowManager::Instance().DestroyWindow(rSlot.pSlotButton);
		}
		if (rSlot.pSignImage)
		{
			CWindowManager::Instance().DestroyWindow(rSlot.pSignImage);
		}
		if (rSlot.pFinishCoolTimeEffect)
		{
			CWindowManager::Instance().DestroyWindow(rSlot.pFinishCoolTimeEffect);
		}
	}

	m_SlotList.clear();

	__DestroyToggleSlotImage();
	__DestroyBaseImage();

	__Initialize();
}

CSlotWindow::CSlotWindow(PyObject * ppyObject) : CWindow(ppyObject)
{
	__Initialize();
}

CSlotWindow::~CSlotWindow()
{
	Destroy();
}
