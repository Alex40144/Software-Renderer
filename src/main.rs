use sdl2::event::Event;
use sdl2::keyboard::Keycode;
use sdl2::pixels::PixelFormatEnum;
use std::ops::Neg;
use std::time::Duration;

const WIDTH: u32 = 800;
const HEIGHT: u32 = 600;
const FOCAL_LENGTH: f32 = 200.0;
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

    let mut obj = obj {
        triangles: vec![
        Triangle {
            p1: Point { x: 0, y: 0, z: 0 },
            p2: Point { x: 200, y: 200, z: 0 },
            p3: Point { x: 200, y: 0, z: 0 },
        },
        Triangle {
            p1: Point { x: 0, y: 0, z: 0 },
            p2: Point { x: 0, y: 200, z: 0 },
            p3: Point { x: 200, y: 200, z: 0 },
        },
        Triangle {
            p1: Point { x: 0, y: 0, z: 0 },
            p2: Point { x: 0, y: 0, z: 200 },
            p3: Point { x: 0, y: 200, z: 0 },
        },
        Triangle {
            p1: Point { x: 0, y: 200, z: 0 },
            p2: Point { x: 0, y: 0, z: 200 },
            p3: Point { x: 0, y: 200, z: 200 },
        },
        ],
        rotation: {
            Rotation {
                x: 0.0,
                y: 0.0,
                z: 0.0,
            }
        },
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
        framedata = vec![0; ((WIDTH*HEIGHT)*4) as usize];

        obj.rotation.x += 0.01;
        obj.rotation.y += 0.05;
        obj.draw(&mut framedata);

        // Update the texture with the framebuffer data
        framebuffer
                .update(None, &framedata, (WIDTH * 4) as usize)
                .expect("Texture update");
        canvas.copy(&framebuffer, None, None).expect("oops");
        canvas.present();
        ::std::thread::sleep(Duration::new(0, 1_000_000_000u32 / 60));
    }

    Ok(())
}

#[derive(Copy, Clone)]
struct Point {
    x: i32,
    y: i32,
    z: i32,
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

#[derive(Copy, Clone)]
struct Rotation {
    x: f32,
    y: f32,
    z: f32,

}

struct obj {
    triangles: Vec<Triangle>,
    rotation: Rotation,
}

trait Draw {
    fn draw(&self, framedata: &mut Vec<u8>);
}

trait DrawWrotation {
    fn draw_with_rotation(&self, framedata: &mut Vec<u8>, rotation: Rotation);
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

impl DrawWrotation for Triangle {
    fn draw_with_rotation(&self, framedata: &mut Vec<u8>, rotation: Rotation) {
        let mut points = [self.p1, self.p2, self.p3];

        for point in points.iter_mut() {
            let x = point.x as f32;
            let y = point.y as f32;
            let z = point.z as f32;

            let firstX = (1.0 * x) + (0.0 * y) + (0.0 * z);
            let firstY = (0.0 * x) + (rotation.x.cos() * y) + (-(rotation.x).sin() * z);
            let firstZ = (0.0 * x) + (rotation.x.sin() * y) + ((rotation.x).cos() * z);

            // Z rotation
            let secondX = (rotation.z.cos() * firstX) + (-(rotation.z).sin() * firstY) + (0.0 * firstZ);
            let secondY = ((rotation.z).sin() * firstX) + ((rotation.z).cos() * firstY) + (0.0 * firstZ);
            let secondZ = (0.0 * firstX) + (0.0 * firstY) + (1.0 * firstZ);
            // Y rotation
            let thirdX = ((rotation.y).cos() * secondX) + (0.0 * secondY) + ((rotation.y).sin() * secondZ);
            let thirdY = (0.0 * secondX) + (1.0 * secondY) + (0.0 * secondZ);
            let thirdZ = (-(rotation.y).sin() * secondX) + (0.0 * secondY) + ((rotation.y).cos() * secondZ);
            // X rotation

            point.x = ((FOCAL_LENGTH * thirdX) / (FOCAL_LENGTH + thirdZ + 500.0) + (WIDTH as f32 / 2.0)) as i32;
            point.y = ((FOCAL_LENGTH * thirdY) / (FOCAL_LENGTH + thirdZ + 500.0) + (HEIGHT as f32 / 2.0)) as i32;
        }

        let line1 = Line {
            p1: points[0],
            p2: points[1],
        };
        let line2 = Line {
            p1: points[1],
            p2: points[2],
        };
        let line3 = Line {
            p1: points[2],
            p2: points[0],
        };
        line1.draw(framedata);
        line2.draw(framedata);
        line3.draw(framedata);
    }
}

impl Draw for obj {
    fn draw(&self, framedata: &mut Vec<u8>) {
        for triangle in self.triangles.iter() {
            triangle.draw_with_rotation(framedata, self.rotation);
        }
    }
}