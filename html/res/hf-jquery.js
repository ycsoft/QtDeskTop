// JavaScript Document
$.fn.extend({
	loadMyApp:function(){
		var sjson = Qt.readFromFile("html/files/my.txt");
		if( sjson == null || sjson.length < 5 )
		{
			var html = '<li class="app" id="add"><a class="appback" href="#"><img src="img/add.png" /><span>添加应用</span></a></li>';
			$("#ulist").html(html);
			$("li#add").readyAdd();
			return;
		}
		var obj = JSON.parse(sjson);
		for ( key in obj )
		{
			var title = key;
			var img = obj[key].img;
			var path = obj[key].file;
			$('#ulist').addApp(img,title,path);	
			var value = new Object;
			value.img = img;
			value.file = path;
			myApps[key] = value;
		}
	},
	//软件中心处使用
	enableDownload:function(){

	$('.download').click(function(e) {
    	var obj = new Object;
		obj.img = $(this).parent().parent().find('img').attr('src');
		obj.title = $(this).parent().find('li.txt').html();
		obj.file = $(this).attr('href');
		Qt.setSoftInfo(JSON.stringify(obj));
		});
	},
	//主界面使用
	addApp:function(src,title,path)
	{
		$('#add').remove();
		var html = $(this).html();
		var obj = new Object;
		obj.img = src;
		obj.file = path;
		myApps[title] = obj;
		html += '<li class="app"><a class="appback" href="'+path+'"><img src="' + src + '" /><span>'+title +'</span></a></li>';
		html += '<li class="app" id="add"><a class="appback" href="#"><img src="img/add.png" /><span>添加应用</span></a></li>';
		$(this).html(html);
		$("li#add").readyAdd();
		$('.appback').click(function(e) {
            var path = $(this).attr('href');
			if ( path == '#'){
				return;	
			}else{
				Qt.exec(path);	
			}
        });

	},

	readyAdd:function(){
				
		$("li#add").click(function(e) {
		Qt.setSoftInfo('');
    	Qt.showWindow('softcenter');
		var softinfo = Qt.getSoftInfo();
		var obj = JSON.parse(softinfo);
		if ( softinfo == '')
		{
			return;
		}else
		{
			if ( obj.title in myApps )
			{
				Qt.msgBox('提示','该软件已经添加');
				return;	
			}
			$('#ulist').addApp(obj.img,obj.title,obj.file);	
			var apps = JSON.stringify(myApps);
			Qt.saveData('html/files/my.txt',apps);
		}
	 })
	},
	setChecked:function(cls,pic){
		var img = $(cls).find('img');
		img.attr('src','');
		img.removeClass('checkimg');
		img = $(this).find('img');
		img.attr('src',pic);
		img.addClass('checkimg');
	}	
});