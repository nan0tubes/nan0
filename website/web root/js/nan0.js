/* Copyright (C) Nan Zero Interactive - All Rights Reserved
 * Unauthorized copying of this file or project, via any medium is strictly prohibited
 * Proprietary and confidential
 * Written by Stephanie Barrett, 2014
 */
 
 /*****************************
 * Vec
 ****************************/
 
 function Vec2 ( x, y )
 {
	this.x = x;
	this.y = y;
 }
 
/*****************************
 * Rect
 ****************************/
function Rect ( left, top, width, height )
{
	this.left = left;
	this.top = top;
	this.width = width;
	this.height = height;
}
Rect.prototype =
{
	GetCenter: function()
	{
		var x = this.left + ( this.width >> 1 );
		var y = this.top + ( this.height >> 1 );
		return new Vec2 ( x, y );
	},
    Contains: function ( point )
    {
        return ( point.x >= this.left && point.x <= this.left + this.width && point.y >= this.top && point.y <= this.top + this.height );
    },
};

function Rect_Renderable ( left, top, width, height )
{
	Rect.call ( this, left, top, width, height );
	
	this.m_lineWidth;
	this.m_strokeStyle;
	this.m_fillStyle;
	this.m_cornerRadius; // in radians (0 - 2, 0 = square)
}
Rect_Renderable.prototype =
{
    SetStroke: function ( lineWidth, strokeStyle )
    {
        this.lineWidth = ( lineWidth <= 0 ) ? 0 : lineWidth;
        this.strokeStyle = strokeStyle;
    },
    SetFill: function ( fillStyle )
    {
        this.fillStyle = fillStyle;
    },
    SetRounded: function ( radius )
    {
        this.cornerRadius = ( radius <= 0 ) ? 0 : radius;
    },
	Draw: function( context )
	{
		context.beginPath();
		// if this Rect has rounded corners
		if ( this.cornerRadius > 0 )
		{
			context.moveTo ( this.left + this.cornerRadius, this.top );
			context.lineTo ( this.left + this.width - this.cornerRadius, this.top );
			context.quadraticCurveTo ( this.left + this.width, this.top, this.left + this.width, this.top + this.cornerRadius );
			context.lineTo ( this.left + this.width, this.top + this.height - this.cornerRadius );
			context.quadraticCurveTo ( this.left + this.width, this.top + this.height, this.left + this.width - this.cornerRadius, this.top + this.height );
			context.lineTo ( this.left + this.cornerRadius, this.top + this.height );
			context.quadraticCurveTo ( this.left, this.top + this.height, this.left, this.top + this.height - this.cornerRadius );
			context.lineTo ( this.left, this.top + this.cornerRadius );
			context.quadraticCurveTo ( this.left, this.top, this.left + this.cornerRadius, this.top );
			context.closePath();
		}
		// else no rounded corners, just draw a normal Rect.
		else
		{
			context.rect ( this.left, this.top, this.width, this.height );
		}
		
		if ( typeof this.fillStyle != "undefined" )
		{
			context.fillStyle = this.fillStyle;
			context.fill();
		}
		
		if ( typeof this.strokeStyle != "undefined" )
		{
			context.lineWidth = this.lineWidth;
			context.strokeStyle = this.strokeStyle;
			context.stroke();
		}
	}
};
Rect_Renderable.prototype = $.extend
(
	{}
	, Rect.prototype
	, Rect_Renderable.prototype
);

/*****************************
 * Label
 ****************************/
// The .font attribute, if set, must be in this order: "[style] [variant] [weight] [size/line-height] [family]"

function Label(text, left, top)
{
    this.text = text;
    this.left = left;
    this.top = top;
    this.font;
    this.textAlign = "Left";
    this.textBaseline = "Bottom";
    this.fillStyle;
    this.strokeStyle;
}
Label.prototype = 
{
    GetTextWidth: function(context)
    {
        return context.measureText(this.text);
    },
    SetFont: function(font)
    {
        this.font = font;
    },
    SetAlign: function(textAlign)
    {
        this.textAlign = textAlign;
    },
    SetBaseline: function(textBaseline)
    {
        this.textBaseline = textBaseline;
    },
    SetFill: function(fillStyle)
    {
        this.fillStyle = fillStyle;
    },
    SetStroke: function(strokeStyle)
    {
        this.strokeStyle = strokeStyle;
    },
    Draw: function(context)
    {
        if (typeof this.font != "undefined")
        {
            context.font = this.font;
        }
    
        context.textAlign = this.textAlign;
        context.textBaseline = this.textBaseline;
    
        // if for some reason neither a fill or a stroke has been defined
        if (typeof this.fillStyle === "undefined" && typeof this.strokeStyle === "undefined")
        {
            context.fillText(this.text, this.left, this.top);
        }
        else
        {
            if (typeof this.fillStyle != "undefined")
            {
                context.fillStyle = this.fillStyle;
                context.fillText(this.text, this.left, this.top);
            }
            // yes, it's possible for your text to be both fill and stroke, be careful.
            if (typeof this.strokeStyle != "undefined")
            {
                context.strokeStyle = this.strokeStyle;
                context.strokeText(this.text, this.left, this.top);
            }
        }
    }
};

/*****************************
 * Button
 ****************************/
 
 function Button ()
 {
	this.hover = false;
	this.active = false;
	this.clicked = false;
	this.rect;
	this.rectHover;
	this.rectActive;
	this.label;
	this.labelHover;
	this.labelActive;
//	document.addEventListener ( "click", this.onClick.bind ( this ), false );
	document.addEventListener ( "mousemove", this.onMouseMove.bind ( this ), false );
	document.addEventListener ( "mousedown", this.onMouseDown.bind ( this ), false );
	document.addEventListener ( "mouseup", this.onMouseUp.bind ( this ), false );
 }
 Button.prototype =
 {
	Draw: function ( context )
	{
		// active state
		if ( this.active )
		{
			if (typeof this.rectActive != "undefined" )
			{
				this.rectActive.Draw ( context );
			}
			else if ( typeof this.rect != "undefined" )
			{
				this.rect.Draw ( context );
			}
			
			if ( typeof this.labelActive != "undefined" )
			{
				this.labelActive.Draw ( context );
			}
			else if (typeof this.label != "undefined" )
			{
				this.label.Draw ( context );
			}
		}
		// hover state
		else if ( this.hover )
		{
			if ( typeof this.rectHover != "undefined" )
			{
				this.rectHover.Draw ( context );
			}
			else if ( typeof this.rect != "undefined" )
			{
				this.rect.Draw ( context );
			}
			
			if ( typeof this.labelHover != "undefined" )
			{
				this.labelHover.Draw ( context );
			}
			else if (typeof this.label != "undefined" )
			{
				this.label.Draw ( context );
			}
		}
		// normal state
		else
		{
			if ( typeof this.rect != "undefined" )
			{
				this.rect.Draw ( context );
			}
			if (typeof this.label != "undefined" )
			{
				this.label.Draw ( context );
			}
		}
	},
	onClick: function ( e )
	{
		var x = e.pageX - canvas.offsetLeft;
		var y = e.pageY - canvas.offsetTop;
		if ( this.rect.Contains ( new Vec2 ( x, y ) ) )
		{
			this.clicked = true;
			console.log("mouseclick");
		}
	},
	onMouseMove: function ( e )
	{
		var x = e.pageX - canvas.offsetLeft;
		var y = e.pageY - canvas.offsetTop;
		if ( this.rect.Contains ( new Vec2 ( x, y ) ) )
		{
			this.hover = true;
		}
		else if ( this.hover == true )
		{
			this.hover = false;
		}
	},
	onMouseDown: function ( e )
	{
		var x = e.pageX - canvas.offsetLeft;
		var y = e.pageY - canvas.offsetTop;
		if ( this.rect.Contains ( new Vec2 ( x, y ) ) )
		{
			this.active = true;
		}
	},
	onMouseUp: function ( e )
	{
		var x = e.pageX - canvas.offsetLeft;
		var y = e.pageY - canvas.offsetTop;
		if ( this.rect.Contains ( new Vec2 ( x, y ) ) )
		{
			if (this.active == true)
			{
				this.clicked = true;
			}
			this.active = false;
		}
		else
		{
			if ( this.active == true )
			{
				this.active = false;
			}
		}
	}
 };
 
/*****************************
 * GameState
 ****************************/

//NOTE: pure virtual class; DON'T INSTANTIATE
function GameState ()
{
}
GameState.prototype =
{
	Update: function ( dt )
	{
		// intentionally empty
		console.log ( "Please override the Update() method in your GameState subclass." );
	},
	Draw: function ( context, screenSize)
	{
		var clearScreen = new Rect_Renderable ( 0, 0, screenSize.x, screenSize.y );
		clearScreen.SetFill ( "#FFF" );
		clearScreen.Draw ( context );
	}
};


/**********************************************************/
   		function GS_Game()
		{
			GameState.call(this);
			
			var rect1 = new Rect_Renderable(10,10,100,100);
			var rect2 = new Rect_Renderable(10,10,100,100);
			var rect3 = new Rect_Renderable(5,5,110,110);
			this.button = new Button();
			rect1.SetFill("#FF0000");
			rect2.SetFill("#FFFF00");
			rect3.SetFill("#00FFFF");
			this.button.rect = rect1;
			this.button.rectHover = rect2
			this.button.rectActive = rect3;
			this.button.label = new Label("text label", 10, 10);
			this.button.label.SetFill("#000000");
		}
		GS_Game.prototype =
		{
			Update: function(dt)
			{
			},
			Draw: function(context, screenSize)
			{
				GameState.prototype.Draw(context, screenSize);
				this.button.Draw(context);
			}
		};
		GS_Game.prototype = $.extend
		(
			{}
			, GameState.prototype
			, GS_Game.prototype
		);
		
		var gameState;
		var now, then;
		
		function main()
		{
			var canvas = document.createElement("canvas");
			canvas.id = "canvas";
			canvas.width = 640;
			canvas.height = 800;
			document.getElementsByTagName("body")[0].appendChild(canvas);
			if (canvas.getContext)
			{
				var context = canvas.getContext("2d");
				gameState = new GS_Game();
				then = new Date().getTime();
				setInterval (
					function()
					{
						now = new Date().getTime();
						var delta = now - then;
						gameState.Update(delta);
						gameState.Draw(context, new Vec2(canvas.width, canvas.height));
						then = now;
					}, 1000/60);
				
			}
		}
