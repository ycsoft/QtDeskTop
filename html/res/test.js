// JavaScript Document
var colMax = 5;

var curRow = 0;
var curCol = 0;

function mouseIn( obj )
{
//	var elem = document.getElementById("all");
	obj.style.backgroundColor = "#666666"; 
}

function mouseOut(obj)
{
	obj.style.backgroundColor = "#2F2F2F"; 
}
function clickTask(txt)
{
	alert(txt.innerHTML);	
}
function addTask(txt)
{
	//$('.debug').debug('addTask');
	var content = $(".content");
	var html = content.html();
	var txt = translate2txt(txt);
	//$('.debug').debug(txt);
	
	html += "<div class='item'>"+ '<div>' + txt + '</div>' + "<a class='itembutton' href='#'><img src='img/dwzw.png' class='applyimg' />申请处理</a>"+"</div>";
	content.html( html );
 $('.item').mouseover(function(e) {
     	var itm = $(this);
		var btn = itm.children("a");
		btn.css('display','block');
});
 $('.item').mouseout(function(e) {
     	var itm = $(this);
		var btn = itm.children("a");
		btn.css('display','none');
});

$('.content').find('a').click(function(e) {
    todoNum += 1;
	var txt = $(this).parent("div").children("div").html();
	$('#headtodo').setNumber(todoNum);
	$('#todo').addToDo(txt,'处理发送');
	//$('a').addToDo(txt,todoNum);
});	
	//$('.debug').debug('addTask Over');
}
function addTaskObj(obj)
{
	//$('.debug').debug('addTask');
	
	var content = $("#apply");
	var html = content.html();
	var txt = obj2html(obj);
	
/*	html += "<span class='item'>"+ '<div>' + txt + '</div>' + "<a class='itembutton' href='#'><img src='img/dwzw.png' class='applyimg' />申请处理/</a>"+"</span>";*/
	content.html( html );
	content.addItem(txt,"处理");
	
 $('.item').mouseover(function(e) {
     	var itm = $(this);
		var btn = itm.children("a");
		btn.css('display','block');
});
 $('.item').mouseout(function(e) {
     	var itm = $(this);
		var btn = itm.children("a");
		btn.css('display','none');
});
/*
$('.item>div').click(function(e) {
	var id = $(this).find("span.id").html();
	$('.detailWindow').children('p').html('');
	var res =  translate2txt(JSON.parse(getbyid(id)));
	$(".detailWindow").find('a').css("display",'block');
	$('.detailWindow').children('p').html(res);
	detailDialog.dialog('open');
});
*/

$('#apply').find('a').click(function(e) {
    todoNum += 1;
	var txt = $(this).parent("span").children("div").html();
	$('#headtodo').setNumber(todoNum);
	$('#todo').addToDo(txt,'处理发送');
	//$('a').addToDo(txt,todoNum);
});	
	//$('.debug').debug('addTask Over');
}

//添加一件事项
function addTask2(txt)
{
	
	var test = txt;//"<h3>项目支出明细</h3><p>单位：国库处</p><p>审核：张三</p><p>摘要:2014年度总共支付543万元，其中....</p>";
	if ( curCol < colMax && curRow > 0)
	{
		if( curRow  >= 1)
		{
			var listElem = document.getElementById('row');
			var lastElem = listElem.nextSibling;
			if( curRow > 1)
			{
				while(lastElem != undefined)
				{
					listElem = lastElem;
					lastElem = lastElem.nextSibling;
				}
			}
		
			var curText = listElem.innerHTML;
			curText = curText + 
			"<div class=\"listtext\">"+
			"<div class=\"block-left\" onclick=\"clickTask(this)\" onmousemove=\"taskMouseIn(this)\" onmouseout=\"taskMouseOut(this)\">"+
			test+
			"</div>"+
			"<div class=\"block-right\"> <hr class=\"vertical\" /></div>"+
			"</div>";
			curCol += 1;
			listElem.innerHTML = curText;
		}
	}else{
		curCol = 1;
		var elemContent = document.getElementById('content');
			
		curText = elemContent.innerHTML + 
		"<hr class=\"hor\" align=\"center\"/><div class=\"row\" id=\"row\">"+
		"<div class=\"listtext\">"+
		"<div class=\"block-left\" onclick=\"clickTask(this)\" onmousemove=\"taskMouseIn(this)\" onmouseout=\"taskMouseOut(this)\">"+
		test+
		"</div>"+
		"<div class=\"block-right\"> <hr class=\"vertical\" /></div>"+
		"</div></div>";
		elemContent.innerHTML = curText;
		curRow += 1;
	}
	
}
function taskMouseIn(obj)
{
	bgstyle = obj.style.backgroundColor;
	obj.style.backgroundColor = "#8080FF"; 
}
function taskMouseOut(obj)
{
	obj.style.backgroundColor = "#D4D4D4";
}

function runQt()
{
	var s = QSimpleMode.invoke();
	alert(s);
}
function reback()
{
	QSimpleMode.returnToAll();
}

function  cfunc_get(sql)
{
	var res = QSimpleMode.get(sql);
	return res;
}

function showMenu()
{
	var pop = window.createPopup();
	//alert(pop);
	  pop.document.oncontextmenu=function(){
                      return false;};
	  pop.show(event.clientX-1,event.clientY,200,2,document.body);
				
}
$.fn.extend({
    setNumber:function(count){
			var img = $(this).find('span.number');
			var numstr = count.toString();		
			if ( count <= 0) 
			{
				numstr = '';
				img.css('display','none');
				//$(this).find('img').css('left','100px');
				return;
			}
			img.html(numstr);
			img.css('display','inline-block');
		}	
	
});

$.fn.extend({
	addItem:function (txt,btnname){
	var numstr = $(this).html();
			numstr += "<span class='item'><div>" + txt + "</div><a class='itembutton' href='#' title='"+btnname+"'><img src='img/dwzw.png' class='applyimg' />"+btnname+"</a></span>";
			
			$(this).html(numstr);
			
			$('.item div').click(function(e) {
			var id = $(this).find("span.id").html();
			$('.detailWindow').children('p').html('');
			var res =  translate2txt(JSON.parse(getbyid(id)));
			res = "<strong>实体编码:<span class='id'>"+id+"</span></strong><p class='data'>" + res + "</p>";
			$("#proc").attr('id',id);
			$(".flowtxt").html(txt);
			var name = $(this).parent('span').find('a').attr('title');
			if ( name != '删除')
			{
				//res += '<div><a class="ui-button" href="#">处理</a></div>';
				$('a.ui-button').css('display','block');
				$('.detailWindow').children('p').html(res);
				detailDialog.dialog('open');
			}else{
				$('a.ui-button').css('display','none');
				$('.detailWindow').children('p').html(res);
				detailDialog.dialog('open');	
			}
			});			
			
			 $('.item').mouseover(function(e) {
     		var itm = $(this);
			var btn = itm.children("a");
				btn.css('display','block');
			});
			$('.item').mouseout(function(e) {
     		var itm = $(this);
			var btn = itm.children("a");
				btn.css('display','none');
			});
			if (btnname != '删除')
			{
				$(this).find('a').click(function(e) {
                	//$(this).parent('span').css("display","none");
					btnname = $(this).attr('title');
					if( btnname == '删除'){
						//done -= 1;
						//$('#headdone').setNumber(done);
						//$(".tips").css('display','block');
						//$("#done").css('height','45%');
						var id = $(this).parent('span').find('span.id').html();
						var res = getbyid(id);
						var sql = "select put('/"+etti + "[" + id+ "]','"+res+"')";
						$(this).popTips('#done',translate2txt(JSON.parse(res)),sql,txt);
						}
            	});
			}
		}
	
});

$.fn.extend({
	addToDo: function (txt,btnname){

			$(this).addItem(txt,btnname);
			//处理任务
			$('#todo').find('a').click(function(e) {
                var itm = $(this).parent("span");
				//itm.css("display","none");
				//todoNum -= 1;
				//done += 1;
				//if ( todoNum < 0)
				//{
				//	todoNum = 0;
				//}
				//$('#headtodo').setNumber(todoNum);
				//$('#headdone').setNumber(done);
				//$('#done').addItem(txt,'删除');
				//发送
				var id = $(this).parent('span').find('span.id').html();
				var res = getbyid(id);
				var sql = "select put('/"+etti + "[" + id+ "]','"+res+"')";
				$(this).popTips('#todo',translate2txt(JSON.parse(res)),sql,txt);
				//$('.debug').debug(sql);
				//Qt.executeSQL(sql);
				//if ( Qt.getRecordCount() > 0 )
				//{
				//	res = Qt.fieldValue(0,0);
				//}
				
            });
			
		}
	
	});
$.fn.extend({
	pages:function(total,cur,fun){
		$(this).jPaginator({ 
	    nbPages:total, 
	    selectedPage:cur,
	    overBtnLeft:'#left_over', 
	    overBtnRight:'#right_over', 
	    maxBtnLeft:'#left_max', 
	    maxBtnRight:'#right_max',
	    minSlidesForSlider:5, 
	    onPageClicked: fun
		//function(a,num) { 
	        //$("#page1").html("demo1 - page : "+num); 
	    //	alert(a);
		//}
	});  
		}
		
});

$.fn.extend({

	pages2:function(total,cur){
		$(this).jPaginator({ 
	    nbPages:total, 
	    selectedPage:cur,
	    overBtnLeft:'#left_over', 
	    overBtnRight:'#right_over', 
	    maxBtnLeft:'#left_max', 
	    maxBtnRight:'#right_max',
	    minSlidesForSlider:5, 
	    onPageClicked: function(a,num) { 

		}
	});  
		}	
	
});
$.fn.extend({

	debug:function(text){
		var ht = $(this).html()+'<br />';
		 $(this).html(ht + text);
		 $(this).css("display","block");
		}	
	
});

$.fn.extend({

popTips:function(id,text,sql,flow){
	/**
	id:   操作id， todo done
	text: 操作的实体数据
	sql:  SQL语句
	flow :要传递到下一界面的数据
	*/
		var self = $(this).parent('span');
		var parent = $(this).parent().parent();
		parent.css('height','45%');
		$("#btmdock").css('bottom','320px');
		$('.tips').css('display','block');
		/*$('.tips').animate({
			 height:'toggle'
			});
		*/	
		var tips = '<h3>数据操作请求</h3><p>操作实体:<span>' + etti + '</span></p><p>操作人:<span></span></p><p>数据内容:<span>'+text+'</span></p>'
		$('.tips-content').html(tips);
		$('.tips .btn').html('<a class="ui-button" id="accept">确认</a><a class="ui-button" id="reject">拒绝</a>');
		$('.tips>img').click(function(e) {
            parent.css('height','70%');
			$("#btmdock").css('bottom','50px');	
			$('.tips').css('display','none');
        });
		
		$("#accept").click(function(e) {
            if ( id == '#todo'){
				todoNum -= 1;
				done += 1;
				$('#headtodo').setNumber(todoNum);
				$('#headdone').setNumber(done);
				$('#done').addItem(flow,'删除');
				Qt.executeSQL(sql);
				$('#todo').css('height','70%');
				$('.tips').css('display','none');
				$("#btmdock").css('bottom','50px');
				
			}else if( id == '#done'){
				done -= 1;
				$('#headdone').setNumber(done);
				$("#done").css('height','70%');
				$("#btmdock").css('bottom','50px');
				$(".tips").css('display','none');
				Qt.executeSQL(sql);			
			}
			self.css('display','none');
			$(this).css('display','none');
        });

		$("#reject").click(function(e) {
            if ( id == '#todo'){
				$('#todo').css('height','70%');
				$('.tips').css('display','none');
				$("#btmdock").css('bottom','50px');
			}else if( id == '#done'){
				$('#headdone').setNumber(done);
				$("#done").css('height','70%');
				$(".tips").css('display','none');
				$("#btmdock").css('bottom','50px');	
			}
        });
		
	}	
});

/////加载任务列表
function getTaskList(host, dbname,usr,pwd)
{
	var res = Qt.connectDB(host,dbname,usr,pwd);
	if ( res == 0 )
	{
		Qt.executeSQL("select getbydate('c016','2015-02-01','')");
		res = Qt.fieldValue(0,0);
		res = json2Array(res);
		return res;
	}else
	{
		Qt.msgBox('Ok','数据库连接失败');	
	}
}

function  json2Array(jstr)
{
	var jsobj = JSON.parse(jstr);
	var res = new Array;
	if ( jsobj instanceof Array)
	{
		
	}
	for ( key in jsobj )
	{
		//ss = JSON.stringify(jsobj[key]);
		//ss = ss.substr(0,100);
		ss = jsobj[key];
		res.push(ss);
	}
	return res;
}
function getType(obj)
{
	if ( obj instanceof Array )
	{
		return 'array';	
	}else{
		if ( obj == null )
		{
			return 'null';
		}else
		{
			return typeof(obj);
		}
	}
}

function transObject( jsobj)
{
	//$('.debug').debug('object');
	var result = '';
	for ( key in jsobj)
	{
		var tp = getType(jsobj[key]);
		//$('.debug').debug(key + ':' + tp);
		if ( tp == 'object' )
		{
			result += '<br />' + key + '为</br>' + transObject(jsobj[key]);	
		}else if ( tp == 'array' )
		{
			result += '<br />' + key + '分别为<br />' + transArray(jsobj[key]);
		}else if ( tp != 'null' ){
			result += key + '为' + jsobj[key] + ',';	
		}
	}
	//$('.debug').debug(result[result.length-1]);
	//$('.debug').debug(result.substr(result.length-1,1));
	if ( result[result.length-1] == ',' )
		{
			result = result.substr(0,result.length-1);	
		}
	result += '<br />';
	return result;
}
function transArray(jsarray)
{
	var result = '';
	for (i in jsarray)
	{
		for ( key in jsarray[i])
		{
			var tp = getType(jsarray[i][key]);
			//$('.debug').debug(key + ':' +tp);
			if ( tp  == 'object' )
			{
				result += key + '为<br />' + transObject(jsarray[i][key]);	
			}else if ( tp  == 'array' )
			{
				result += key + '分别为<br />' + transArray(jsarray[i][key]);
			}else if ( tp != 'null' )
			{
				result += key + '为' + jsarray[i][key] + ',';	
			}
		}
		if ( result[result.length-1] == ',' )
		{
			result = result.substr(0,result.length-1);	
		}
		//$('.debug').debug(result[result.length-1]);
		//$('.debug').debug(result.indexOf(',',result.length-2));
		result += ';<br />';
	}	
	
	result += '<br />';
	return result;
}
function translate2txt(jsobj)
{
	var result = '';
	if (  getType(jsobj) == 'object' )
	{
		
		return transObject( jsobj);
		
	}else if (  getType(jsobj) == 'array')
	{
		
		return transArray( jsobj)
	}
}
///
function getList(tb,gw)
{
	var result = new Array;
	var res = Qt.connectDB('127.0.0.1','fasp_yz','postgres','postgres');
	if ( res == 0 )
	{
		var sql ="select * from getbyettilist('"+tb+"','"+gw + "') as (id numeric(20,0),c1 varchar(100),c2 varchar(100),c3 varchar(30));";
		Qt.executeSQL(sql);
		var rows = Qt.getRecordCount();
		for ( var i = 0 ; i < rows; i++)
		{
			robj = new Object;
			robj.id = Qt.fieldValue(i,0);
			robj.code = Qt.fieldValue(i,1);
			robj.remark = Qt.fieldValue(i,2);
			robj.date = Qt.fieldValue(i,3);
			//$('.debug').debug(sql);
			result.push(robj);
		}
		return result;
	}else
	{
		Qt.msgBox('Ok','数据库连接失败');	
	}

}
function  obj2html( obj )
{
	var res = '';
	res = '<p id="id" align="left"><strong>ID:</strong><span class="id">' + obj.id + '</span></p>';
	res += '<p  align="left"><strong>单号:</strong><span>' + obj.code + '</span></p>';
	res += '<p  align="left"><strong>日期:</strong><span>' + obj.date + '</span></p>';
	res += '<p  align="left"><strong>摘要:</strong><span>' + obj.remark + '</span></p>';

	return res;	
}
function getbyid( id )
{
	var sql = "select * from getbyid('"+etti+"','" + id + "')";
	Qt.executeSQL(sql);
	if ( Qt.getRecordCount() > 0 )
	{
		//$('.debug').debug(sql);
		var res = Qt.fieldValue(0,0);
		return res;
	}else
	{
		return '';
	}
}