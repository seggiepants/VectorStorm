#pragma once

#ifndef __SCENE_H__
#define __SCENE_H__

class Scene
{
public:
	Scene();
	virtual void Init();
	virtual Scene* Update(float dt);
	virtual void Draw();
private:

};

#endif

