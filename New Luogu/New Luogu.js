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
	 * 统计字符串行数
	 * @param {string} str 要统计行数的字符串
	 * @returns 字符串行数
	 */
	function countLine(str){
		const match = str.match(/\r\n|\n/g);
		return match?match.length + 1:1;
	}

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

	/**
	 * 将 Markdown 文本转换成 HTML 文本
	 * @param {string} md Markdown 文本
	 * @returns HTML 文本
	 */
	function md2HTML(md){
		let HTML = md.replace(/^```(\w*)(?: +(line-numbers))?.*?\n([\s\S]*?)\n```$/gm,function(match,lang,n,code){
			console.log('代码块 match 调试:',match);

			const langlst = [
				'plain',
				'cpp',
				'python',
				'c',
				'java',
				'javascript',
				'markdown',
				'latex'
			];

			if (!lang){
				lang = 'plain';
			}else if (!langlst.includes(lang)){
				lang = 'cpp';
			}
			const ln = '				<span style="height: 21px;"></span>\n'.repeat(countLine(code));
			code.replace(/[<>&"']/g,function(m){
				switch (m){
					case '&':	return '&amp;';
					case '<':	return '&lt;';
					case '>':	return '&gt;';
					case '"':	return '&quot;';
					case "'":	return '&#39;';
					default:	return m;
				}
			});

			let res = `
<div data-v-a7061ca4="" class="code-container">
	<pre data-v-a7061ca4="" data-line="" class="pre line-numbers ${n?' ':'hide-numbers '}language-${lang}" tabindex="0">
		<code data-v-a7061ca4="" class="language-${lang}">
			${code}
			<span aria-hidden="true" class="line-numbers-rows">
${ln}
			</span>
			<span class="line-numbers-sizer" style="display: none;"></span>
		</code>
	</pre>
	<button data-v-a7061ca4="" type="button" class="copy-button">
		<svg data-v-a7061ca4="" class="svg-inline--fa fa-copy copy-icon" aria-hidden="true" focusable="false" data-prefix="fas" data-icon="copy" role="img" xmlns="http://www.w3.org/2000/svg" viewBox="0 0 448 512">
			<path class="" fill="currentColor" d="M208 0L332.1 0c12.7 0 24.9 5.1 33.9 14.1l67.9 67.9c9 9 14.1 21.2 14.1 33.9L448 336c0 26.5-21.5 48-48 48l-192 0c-26.5 0-48-21.5-48-48l0-288c0-26.5 21.5-48 48-48zM48 128l80 0 0 64-64 0 0 256 192 0 0-32 64 0 0 48c0 26.5-21.5 48-48 48L48 512c-26.5 0-48-21.5-48-48L0 176c0-26.5 21.5-48 48-48z"></path>
		</svg>
	</button>
</div>
`;
			console.log('代码块 res 调试:',res);
			return res;
		});
		console.log("简单转换:",HTML);

		HTML = marked.parse(HTML);
		return HTML;
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
			const userInfoHTML = md2HTML(userInfoMD);
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