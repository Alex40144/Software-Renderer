use sdl2::event::Event;
use sdl2::keyboard::Keycode;
use sdl2::pixels::PixelFormatEnum;
use std::ops::Neg;

const WIDTH: u32 = 800;
const HEIGHT: u32 = 600;
fn main() -> Result<(), String> {
    let sdl_context = sdl2::init().unwrap();
    let video_subsystem = sdl_context.video().unwrap();

    let window = video_subsystem
        .window("Software Renderer", WIDTH, HEIGHT)
        .position_centered()
        .build()
        .unwrap();

    let mut canvas = window.into_canvas().build().unwrap();

    let texture_creator = canvas.texture_creator();
    let mut framebuffer = texture_creator
        .create_texture_streaming(Some(PixelFormatEnum::ARGB8888), WIDTH, HEIGHT)
        .unwrap();

    let mut framedata: Vec<u8> = vec![0; ((WIDTH*HEIGHT)*4) as usize];


    let triangle = Triangle {
        p1: Point { x: 100, y: 100 },
        p2: Point { x: 200, y: 200 },
        p3: Point { x: 200, y: 100 },
    };

    let triangle2 = Triangle {
        p1: Point { x: 100, y: 100 },
        p2: Point { x: 100, y: 200 },
        p3: Point { x: 200, y: 200 },
    };

    let mut event_pump = sdl_context.event_pump()?;
    'running: loop {
        
        for event in event_pump.poll_iter() {
            match event {
                Event::Quit {..} |
                Event::KeyDown { keycode: Some(Keycode::Escape), .. } => {
                    break 'running;
                },
                _ => {}
            }
        }

        triangle.draw(&mut framedata);
        triangle2.draw(&mut framedata);

        // Update the texture with the framebuffer data
        framebuffer
                .update(None, &framedata, (WIDTH * 4) as usize)
                .expect("Texture update");
        canvas.copy(&framebuffer, None, None).expect("oops");
        canvas.present();
    }

    Ok(())
}

#[derive(Copy, Clone)]
struct Point {
    x: i32,
    y: i32,
}
struct Line {
    p1: Point,
    p2: Point,
}

struct Triangle {
    p1: Point,
    p2: Point,
    p3: Point,
}

trait Draw {
    fn draw(&self, framedata: &mut Vec<u8>);
}

impl Draw for Line {
    fn draw(&self, framedata: &mut Vec<u8>) {
        let mut x1 = self.p1.x;
        let mut y1 = self.p1.y;
        let x2 = self.p2.x;
        let y2 = self.p2.y;

        let dx = (x2 - x1).abs();
        let sx = if x1 < x2 { 1 } else { -1 };
        let dy = (y2 - y1).abs().neg();
        let sy = if y1 < y2 {1} else {-1};
        let mut error = dx + dy;

        loop {
            if (x1 + y1 * (WIDTH as i32)) < (WIDTH * HEIGHT) as i32 {
                framedata[((x1 + (y1 * WIDTH as i32)) as usize) * 4 ] = 0xff;
                framedata[((x1 + y1 * WIDTH as i32) as usize) * 4 + 1 ] = 0xff;
                framedata[((x1 + y1 * WIDTH as i32) as usize) * 4 + 2 ] = 0xff;
                framedata[((x1 + y1 * WIDTH as i32) as usize) * 4 + 3] = 0xff;
            }
            if x1 == x2 && y1 == y2 {break;}
            let e2 = 2 * error;
            if e2 >= dy {
                if x1 == x2 {break;}
                error = error + dy;
                x1 = x1 + sx;
            }
            if e2 <= dx {
                if y1 == y2 {break;}
                error = error + dx;
                y1 = y1 + sy;
            }
        }
    }
}

impl Draw for Triangle {
    fn draw(&self, framedata: &mut Vec<u8>) {
        let line1 = Line {
            p1: self.p1,
            p2: self.p2,
        };
        let line2 = Line {
            p1: self.p2,
            p2: self.p3,
        };
        let line3 = Line {
            p1: self.p3,
            p2: self.p1,
        };
        line1.draw(framedata);
        line2.draw(framedata);
        line3.draw(framedata);
    }
}