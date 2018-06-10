var gulp = require('gulp');
var sourcemaps = require('gulp-sourcemaps');
var babel = require('gulp-babel');
var concat = require('gulp-concat');

var sass = require('gulp-sass');
var uglify = require('gulp-uglify');
var pleeease = require('gulp-pleeease');
var browserify = require('browserify');
var babelify = require('babelify');
var source = require('vinyl-source-stream');
var buffer = require('vinyl-buffer');

gulp.task('server:watch', () => {
    gulp.watch('./src/server/*.js', ['server:build']);
});

gulp.task('server:build', () => {
    gulp.src('./src/server/*.js')
        .pipe(sourcemaps.init())
        .pipe(babel({ presets: ['es2015'] }))
        .pipe(gulp.dest('./dist/server'));
});

gulp.task('client:watch', () => {
    gulp.watch('./src/client/js/*.js', ['client:build:js']);
    gulp.watch('./src/client/scss/*.scss', ['client:build:scss']);
});

gulp.task('client:build:js', () => {
    browserify('./src/client/js/main.js', { debug: false })
        .transform(babelify.configure({
            presets: ['es2015']
        }))
        .bundle()
        .pipe(source('main.js'))
        .pipe(buffer())
        .pipe(uglify())
        .pipe(gulp.dest('./dist/client'));
});

gulp.task('client:build:scss', () => {
    gulp.src('./src/client/scss/style.scss')
        .pipe(
            sass({outputStyle: 'compressed'})
            .on('error', sass.logError)
        )
        .pipe(pleeease({
            fallbacks: {
                autoplefixer: ['last 4 versions']
            }
        }))
        .pipe(gulp.dest('./dist/client/'));
});

gulp.task('watch', ['server:watch', 'client:watch']);

gulp.task('build', ['server:build', 'client:build:js', 'client:build:scss']);
