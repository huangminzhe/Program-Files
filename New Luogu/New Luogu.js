// ==UserScript==
// @name		New Luogu
// @namespace	https://www.cnblogs.com/Lin-morning
// @version		1.0
// @description	A Better Luogu!
// @author		Lin_morning
// @match		https://www.luogu.com.cn/user/*
// @grant		GM_xmlhttpRequest
// @require		https://cdn.jsdelivr.net/npm/marked/marked.min.js
// ==/UserScript==

(async function() {
	'use strict';
	const IntroducitonID = 'New Luogu Introduction';

	/**
	 * @returns 用户 UID
	 */
	function getUID(){
		const match = window.location.pathname.match(/\/user\/(\d+)/);
		return match[0] == match.input?match[1]:null;
	}

	/**
	 * 使用异步才能获取数据
	 * @returns 个人简介
	 */
	async function getIntroduction(){
		return new Promise((result,reject) => {
			const uid = getUID();
			if (!uid){
				console.warn('无法获取 UID');
				reject(new Error('无法获取 UID'));
			}else{
				console.log('UID:',uid);

				const apiURL = `https://www.luogu.com.cn/api/user/info/${uid}`;
				console.log('开始请求',apiURL);
				GM_xmlhttpRequest({
					method: 'GET',
					url: apiURL,
					onload: function(res){
						try {
							console.log('成功获取',uid,'的数据');
							const userInfo = JSON.parse(res.responseText);
							console.log('成功解析 JSON 数据');
							result(userInfo.user.introduction);
						}catch (err){
							console.error('无法解析数据:',err);
							reject(err);
						}
					},
					onerror: function(err){
						console.error('无法获取',uid,'的数据:',err);
						reject(err);
					}
				});
			}
		});
	}

	// 于个人主页装填个人简介
	let lastUrl = location.href;
	let timer = null;
	const createIntroduction = new MutationObserver(function() {
		clearTimeout(timer);
		timer = setTimeout(async function(){
			if (location.href !== lastUrl) {
				console.log('检测到 URL 变化');
				lastUrl = location.href;
			}

			const userInfoMD = await getIntroduction();
			const userInfoHTML = marked.parse(userInfoMD);
			console.log('获取到用户简介:',userInfoHTML);

			const parent = document.querySelectorAll('div.main')[1];	// 父容器
			console.log('获取到父容器:',parent);

			const itdct = document.createElement('div');	// 个人介绍 div
			itdct.id = IntroducitonID;
			itdct.className = 'l-card';
			itdct.setAttribute('data-v-c3407962','');
			itdct.setAttribute('data-v-f4fefeb2','');
			itdct.setAttribute('data-v-754e1ea4-s','');
			itdct.innerHTML = `
<div data-v-f4fefeb2="" class="header">
	<h3 data-v-f4fefeb2="" style="margin: 0px;">个人介绍（仅 New Luogu 可见）</h3>
</div>
<div data-v-f4fefeb2="" class="lfe-marked-wrap introduction">
	<div class="lfe-marked">
		${userInfoHTML}
	</div>
</div>
`;
			if (!document.getElementById(IntroducitonID)){
				parent.prepend(itdct);
			}
		},1000);
	});
	createIntroduction.observe(document.getElementById('app'),{childList: true,subtree: true});
})();