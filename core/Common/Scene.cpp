#include "..\ebase.h"
#include "..\enode.h"
#include "..\emanager.h"

e2d::Scene::Scene()
	: m_bWillSave(true)
	, m_bAutoUpdate(true)
	, m_bSortNeeded(false)
	, m_bColliderVisiable(false)
	, m_pRoot(new Node())
{
	m_pRoot->retain();
	m_pRoot->_onEnter();
	m_pRoot->_setParentScene(this);
}

e2d::Scene::~Scene()
{
	SafeRelease(&m_pRoot);
}

void e2d::Scene::_render()
{
	m_pRoot->_render();

	if (m_bColliderVisiable)
	{
		// 恢复矩阵转换
		Renderer::getRenderTarget()->SetTransform(D2D1::Matrix3x2F::Identity());
		// 绘制所有几何图形
		m_pRoot->_drawCollider();
	}
}

void e2d::Scene::_update()
{
	// 执行 onUpdate 函数
	if (m_bAutoUpdate)
	{
		this->onUpdate();
	}
	// 更新根节点
	m_pRoot->_update();
}

void e2d::Scene::setAutoUpdate(bool bAutoUpdate)
{
	m_bAutoUpdate = bAutoUpdate;
}

void e2d::Scene::add(Node * child, int order /* = 0 */)
{
	m_pRoot->addChild(child, order);
}

#if HIGHER_THAN_VS2012
void e2d::Scene::add(const InitList<Node*>& vNodes, int order)
{
	for (const auto &node : vNodes)
	{
		this->add(node, order);
	}
}
#endif

bool e2d::Scene::remove(Node * child)
{
	return m_pRoot->removeChild(child);
}

e2d::Node * e2d::Scene::getRoot() const
{
	return m_pRoot;
}

void e2d::Scene::showCollider(bool visiable)
{
	m_bColliderVisiable = visiable;
}
